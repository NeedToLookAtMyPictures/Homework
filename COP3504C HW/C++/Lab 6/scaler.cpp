#include <iostream>
#include <string>
#include <vector>
#include "ConsoleGfx.h"
#include "Image.h"


unsigned char* scaledImage(const unsigned char* imageData, int orders)
{
    if (orders < 1 || orders > 4)
    {
        std::cerr << "Scale must be between 1 and 4." << std::endl;
    }

    //If orders is too high this find the lowest possible order such that dimensions won't exceed 256
    if (orders * imageData[0] > 256 || orders * imageData[1] > 256)
    {
        for (int i = orders; i > 0; i--)
        {
            if (i * imageData[0] > 256 || i * imageData[1] > 256)
            {
                continue;
            }
            else
            {
                orders = i;
                break;
            }
        }
    }

    //pow(2,scale), converts order to the practical scaling it would apply
    int scale = 1;
    for (int i = 0; i < orders; i++)
    {
        scale *= 2;
    }

    //Get the new enlarged height and width
    int newW = scale * imageData[0]; //WIDTH
    int newH = scale * imageData[1]; //HEIGHT

    //Limit dimensions of scaled image to 256 x 256
    if (newW > 256)
    {
        newW = 256;
    }
    if (newH > 256)
    {
        newH = 256;
    }

    //2D vector for pixelData construction
    std::vector<std::vector<unsigned char>> pixelData(newH, std::vector<unsigned char>(newW));
    //format: std::vector<std::vector<int> > vec(ROW_COUNT, std::vector<var>(COLUMN_COUNT))

    //2D vector for imageData referencing
    std::vector<std::vector<unsigned char>> OGpixelData(newH, std::vector<unsigned char>(newW));
    for (int y = 0; y < imageData[1]; y++)
    {
        for (int x = 0; x < imageData[0]; x++)
        {
            OGpixelData[y][x] = imageData[2 + x + (imageData[0] * y)];
        }
    }

    //Construct pixelData
    for (int x = 0; x < newW; x++)
    {
        for (int y = 0; y < newH; y++)
        {
            int srcX = (x * imageData[0]) / newW;
            int srcY = (y * imageData[1]) / newH;

            pixelData[y][x] = OGpixelData[srcY][srcX];
        }
    }

    //Convert pixelData into proper output
    unsigned char* scaledImageData = new unsigned char[newW * newH + 2];
    scaledImageData[0] = newW;
    scaledImageData[1] = newH;
    for (int y = 0; y < newH; y++)
    {
        for (int x = 0; x < newW; x++)
        {
            scaledImageData[2 + x + (y * newW)] = pixelData[y][x];
        }
    }
    return scaledImageData;





}

int main()
{
    //Fetch ConsoleGfx via ConsoleGfx.getInstance()
    auto* gfx = ConsoleGfx::getInstance();

    //Display welcome message
    std::cout << "Welcome to the Image Scaler!\n\nDisplaying Spectrum Image:" << std::endl;

    //Display color test (ConsoleGfx.testRainbow)
    gfx->displayImage(gfx->testRainbow);

    //Create Image object
    Image* myImage = nullptr;
    bool exit = false;
    while (!exit)
    {
        //Display the menu
        std::cout << "\nScaler Menu"
                "\n-----------"
                "\n0. Exit"
                "\n1. Load File"
                "\n2. Load Test Image"
                "\n3. Display Image"
                "\n4. Enlarge Image"
                "\n5. Shrink Image"
                "\n6. Show Image Properties"
                "\n\nSelect a Menu Option: " << std::flush;
        //Prompt for input
        int choice;
        std::cin >> choice;
        std::string fileName;
        unsigned char* load;
        switch(choice)
        {
        default:
            std::cout << "why am I showing up" << std::endl;
            break;
        case 0:
            //Exit
            exit = true;
            break;
        case 1:
            //Load File
            std::cout << "Enter name of file to load: " << std::flush;
            std::cin >> fileName;
            load = gfx->loadFile(fileName);
            if (load == nullptr)
            {
                //Not a valid file
                std::cout << "Error: could not load file." << std::endl;
            }
            else
            {
                //Valid file
                std::cout << "File loaded." << std:: endl;
                delete myImage;
                myImage = new Image(load);
            }
            break;
        case 2:
            //Load Test Image
            std::cout << "Test image data loaded." << std::endl;
            delete myImage;
            myImage = new Image(gfx->testImage);
            break;
        case 3:
            //Display Image
            if (myImage == nullptr)
            {
                std::cout << "Error: no image loaded." << std::endl;
            }
            else
            {
                gfx->displayImage(myImage->getImageData());
            }
            break;
        case 4:
            //Enlarge Image
            if (myImage == nullptr)
            {
                std::cout << "Error: no image loaded." << std::endl;
            }
            else
            {
                int scale;
                std::cout << "Enter orders of magnitude for enlargement: " << std::flush;
                std::cin >> scale;
                unsigned char* scaledData = scaledImage(myImage->getImageData(), scale);
                delete myImage;
                myImage = new Image(scaledData);
            }
                break;
        case 5:
            //Shrink Image
            std::cout << "Don't need to do shrink" << std::endl;
            break;
        case 6:
            //Show Image Properties
            if (myImage == nullptr)
            {
                std::cout << "Error: no image loaded." << std::endl;
            }
            else
            {
                std::cout << "Image Dimensions: (" << static_cast<unsigned>(myImage->getWidth()) << ", " << static_cast<unsigned>(myImage->getHeight()) << ")" << std::endl;
            }
            break;
        }
    }
    return 0;
}