#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include "header.h"
#include "pixel.h"

// COMPLETE

std::vector<float> generalizer(Pixel pxl)
{
    std::vector<float> Pixels;
        Pixels.push_back(pxl.Blue / 255.0f);
        Pixels.push_back(pxl.Green / 255.0f);
        Pixels.push_back(pxl.Red / 255.0f);
    return Pixels;
}

Pixel multiply(Pixel pixel1, Pixel pixel2)
{
    // converts 0-255 chars into 0-1 floats
    std::vector<float> Pixel1 = generalizer(pixel1);
    std::vector<float> Pixel2 = generalizer(pixel2);

    // manipulates Pixel1 and Pixel2 into one PixelFinal
    std::vector<float> multPixel;
    // (Pixel1 * Pixel2) * 255 + 0.5
    multPixel.push_back(std::min(255.0, Pixel1.at(0) * Pixel2.at(0) * 255 + 0.5));
    multPixel.push_back(std::min(255.0, Pixel1.at(1) * Pixel2.at(1) * 255 + 0.5));
    multPixel.push_back(std::min(255.0, Pixel1.at(2) * Pixel2.at(2) * 255 + 0.5));

    Pixel finalPixel;
    finalPixel.Blue = static_cast<char>(multPixel.at(0));
    finalPixel.Green = static_cast<char>(multPixel.at(1));
    finalPixel.Red = static_cast<char>(multPixel.at(2));
    return finalPixel;
}

Pixel subtract(Pixel pixel1, Pixel pixel2)
{
    // converts 0-255 chars into 0-1 floats
    std::vector<float> Pixel1 = generalizer(pixel1);
    std::vector<float> Pixel2 = generalizer(pixel2);

    // manipulates Pixel1 and Pixel2 into one PixelFinal
    std::vector<float> subPixel;
    subPixel.push_back(std::max(0.0, Pixel2.at(0) - Pixel1.at(0) + 0.0) * 255 + 0.5);
    subPixel.push_back(std::max(0.0, Pixel2.at(1) - Pixel1.at(1) + 0.0) * 255 + 0.5);
    subPixel.push_back( std::max(0.0, Pixel2.at(2) - Pixel1.at(2) + 0.0) * 255 + 0.5);

    Pixel finalPixel;
    finalPixel.Blue = static_cast<char>(subPixel.at(0));
    finalPixel.Green = static_cast<char>(subPixel.at(1));
    finalPixel.Red = static_cast<char>(subPixel.at(2));
    return finalPixel;
}

Pixel screen(Pixel pixel1, Pixel pixel2)
{
    // converts 0-255 chars into 0-1 floats
    std::vector<float> Pixel1 = generalizer(pixel1);
    std::vector<float> Pixel2 = generalizer(pixel2);

    // manipulates Pixel1 and Pixel2 into one PixelFinal
    std::vector<float> screenPixel;
    screenPixel.push_back(std::min(255.0, (1 - (1 - Pixel1.at(0)) * (1 - Pixel2.at(0))) * 255 + 0.5));
    screenPixel.push_back(std::min(255.0, (1 - (1 - Pixel1.at(1)) * (1 - Pixel2.at(1))) * 255 + 0.5));
    screenPixel.push_back(std::min(255.0, (1 - (1 - Pixel1.at(2)) * (1 - Pixel2.at(2))) * 255 + 0.5));

    Pixel finalPixel;
    finalPixel.Blue = static_cast<char>(screenPixel.at(0));
    finalPixel.Green = static_cast<char>(screenPixel.at(1));
    finalPixel.Red = static_cast<char>(screenPixel.at(2));
    return finalPixel;
}

Pixel overlay(Pixel pixel1, Pixel pixel2)
{
    // converts 0-255 chars into 0-1 floats
    std::vector<float> Pixel1 = generalizer(pixel1);
    std::vector<float> Pixel2 = generalizer(pixel2);

    // manipulates Pixel1 and Pixel2 into one PixelFinal
    std::vector<float> overPixel;
    if (Pixel2.at(0) <= 0.5 || Pixel2.at(1) <= 0.5 || Pixel2.at(2) <= 0.5)
    {
        overPixel.push_back(std::min(255.0, 2 * Pixel1.at(0) * Pixel2.at(0) * 255 + 0.5));
        overPixel.push_back(std::min(255.0, 2 * Pixel1.at(1) * Pixel2.at(1) * 255 + 0.5));
        overPixel.push_back(std::min(255.0, 2 * Pixel1.at(2) * Pixel2.at(2) * 255 + 0.5));
    }
    else
    {
        // 1 - 2 * (1 - Pixel1) * (1 - Pixel2)
        overPixel.push_back(std::min(255.0, (1 - 2 * (1 - Pixel1.at(0)) * (1 - Pixel2.at(0))) * 255 + 0.5));
        overPixel.push_back(std::min(255.0, (1 - 2 * (1 - Pixel1.at(1)) * (1 - Pixel2.at(1))) * 255 + 0.5));
        overPixel.push_back(std::min(255.0, (1 - 2 * (1 - Pixel1.at(2)) * (1 - Pixel2.at(2))) * 255 + 0.5));
    }

    Pixel finalPixel;
    finalPixel.Blue = static_cast<char>(overPixel.at(0));
    finalPixel.Green = static_cast<char>(overPixel.at(1));
    finalPixel.Red = static_cast<char>(overPixel.at(2));
    return finalPixel;
}

int tester(std::ifstream& myFile, std::ifstream& exampleFile)
{
    Header headerFiller;
    myFile.read(reinterpret_cast<char *>(&headerFiller), 18);
    headerFiller = {};
    exampleFile.read(reinterpret_cast<char *>(&headerFiller), 18);
    std::vector<Pixel> myData(headerFiller.height * headerFiller.width);
    std::vector<Pixel> exampleData(headerFiller.height * headerFiller.width);
    for (int i = 0; i < headerFiller.height * headerFiller.width; i++)
    {
        myFile.read(reinterpret_cast<char *>(&myData[i]), sizeof(Pixel));
        exampleFile.read(reinterpret_cast<char *>(&exampleData[i]), sizeof(Pixel));
    }
    for (int i = 0; i < headerFiller.height * headerFiller.width; i++)
    {
        if(exampleData.at(i).Blue != myData.at(i).Blue || exampleData.at(i).Green != myData.at(i).Green || exampleData.at(i).Red != myData.at(i).Red)
        {
            return false;
        }
    }
    return true;
}


int main()
{
    std::ifstream file1;
    std::ifstream file2;
    std::ifstream file3;
    std::ifstream file4;
    std::ofstream outFile;

    // Part 1 -----------------------------------------------------------------------
    file1.open("input/layer1.tga", std::ios::binary);
    file2.open("input/pattern1.tga", std::ios::binary);
    outFile.open("output/part1.tga", std::ios::binary);
    Header headerUse, headerFiller;
    // reads header data from images into respective header objects
    file1.read(reinterpret_cast<char *> (&headerUse), 18);
    file2.read(reinterpret_cast<char *> (&headerFiller), 18);
    // create vector for image data
    Pixel* imageData = new Pixel[headerUse.width * headerUse.height];
    // read image data from image into BGR array
    for (int i = 0; i < headerUse.height * headerUse.width; i++)
    {
        if (!file1.is_open())
        {
            std::cout << "woops" << std::endl;
        }
        Pixel pxl1, pxl2;
        // Pixel from file1
        file1.read(reinterpret_cast<char *> (&pxl1.Blue), sizeof(pxl1.Blue));
        file1.read(reinterpret_cast<char *> (&pxl1.Green), sizeof(pxl1.Green));
        file1.read(reinterpret_cast<char *> (&pxl1.Red), sizeof(pxl1.Red));
        // Pixel from file2
        file2.read(reinterpret_cast<char *> (&pxl2.Blue), sizeof(pxl2.Blue));
        file2.read(reinterpret_cast<char *> (&pxl2.Green), sizeof(pxl2.Green));
        file2.read(reinterpret_cast<char *> (&pxl2.Red), sizeof(pxl2.Red));
        // multiply
        imageData[i] = multiply(pxl1, pxl2);
    }
    file1.close();
    file2.close();
    // write header data into output file
    outFile.write(reinterpret_cast<char *> (&headerUse), sizeof(headerUse));
    // write image data into output file
    for (int i = 0; i < headerUse.height * headerUse.width; i++)
    {
        outFile.write(reinterpret_cast<char *> (&imageData[i]), sizeof(imageData[i]));
    }
    outFile.close();
    delete[] imageData;
    headerUse = {};
    headerFiller = {};


    // Part 2 -----------------------------------------------------------------------
    file1.open("input/layer2.tga", std::ios::binary);
    file2.open("input/car.tga", std::ios::binary);
    outFile.open("output/part2.tga", std::ios::binary);
    // reads header data from images into respective header objects
    file1.read(reinterpret_cast<char *> (&headerUse), 18);
    file2.read(reinterpret_cast<char *> (&headerFiller), 18);
    // create vector for image data
    imageData = new Pixel[headerUse.width * headerUse.height];
    // read image data from image into BGR array
    for (int i = 0; i < headerUse.height * headerUse.width; i++)
    {
        if (!file1.is_open())
        {
            std::cout << "woops" << std::endl;
        }
        Pixel pxl1, pxl2;
        // Pixel from file1
        file1.read(reinterpret_cast<char *> (&pxl1.Blue), sizeof(pxl1.Blue));
        file1.read(reinterpret_cast<char *> (&pxl1.Green), sizeof(pxl1.Green));
        file1.read(reinterpret_cast<char *> (&pxl1.Red), sizeof(pxl1.Red));
        // Pixel from file2
        file2.read(reinterpret_cast<char *> (&pxl2.Blue), sizeof(pxl2.Blue));
        file2.read(reinterpret_cast<char *> (&pxl2.Green), sizeof(pxl2.Green));
        file2.read(reinterpret_cast<char *> (&pxl2.Red), sizeof(pxl2.Red));
        // subtract
        imageData[i] = subtract(pxl1, pxl2);
    }
    file1.close();
    file2.close();
    // write header data into output file
    outFile.write(reinterpret_cast<char *> (&headerUse), sizeof(headerUse));
    // write image data into output file
    for (int i = 0; i < headerUse.height * headerUse.width; i++)
    {
        outFile.write(reinterpret_cast<char *> (&imageData[i]), sizeof(imageData[i]));
    }
    outFile.close();
    delete[] imageData;
    headerUse = {};
    headerFiller = {};

    // Part 3 -----------------------------------------------------------------------
    file1.open("input/layer1.tga", std::ios::binary);
    file2.open("input/pattern2.tga", std::ios::binary);
    outFile.open("output/temp-part3.tga", std::ios::binary);
    // reads header data from images into respective header objects
    file1.read(reinterpret_cast<char *> (&headerUse), 18);
    file2.read(reinterpret_cast<char *> (&headerFiller), 18);
    // create vector for image data
    imageData = new Pixel[headerUse.width * headerUse.height];
    // read image data from image into BGR array
    for (int i = 0; i < headerUse.height * headerUse.width; i++)
    {
        if (!file1.is_open())
        {
            std::cout << "woops" << std::endl;
        }
        Pixel pxl1, pxl2;
        // Pixel from file1
        file1.read(reinterpret_cast<char *> (&pxl1.Blue), sizeof(pxl1.Blue));
        file1.read(reinterpret_cast<char *> (&pxl1.Green), sizeof(pxl1.Green));
        file1.read(reinterpret_cast<char *> (&pxl1.Red), sizeof(pxl1.Red));
        // Pixel from file2
        file2.read(reinterpret_cast<char *> (&pxl2.Blue), sizeof(pxl2.Blue));
        file2.read(reinterpret_cast<char *> (&pxl2.Green), sizeof(pxl2.Green));
        file2.read(reinterpret_cast<char *> (&pxl2.Red), sizeof(pxl2.Red));
        // multiply
        imageData[i] = multiply(pxl1, pxl2);
    }
    file1.close();
    file2.close();
    // write header data into output file
    outFile.write(reinterpret_cast<char *> (&headerUse), sizeof(headerUse));
    // write image data into output file
    for (int i = 0; i < headerUse.height * headerUse.width; i++)
    {
        outFile.write(reinterpret_cast<char *> (&imageData[i]), sizeof(imageData[i]));
    }
    outFile.close();
    delete[] imageData;
    headerUse = {};
    headerFiller = {};

    file1.open("input/text.tga", std::ios::binary);
    file2.open("output/temp-part3.tga", std::ios::binary);
    outFile.open("output/part3.tga", std::ios::binary);
    // reads header data from images into respective header objects
    file1.read(reinterpret_cast<char *> (&headerUse), 18);
    file2.read(reinterpret_cast<char *> (&headerFiller), 18);
    // create vector for image data
    imageData = new Pixel[headerUse.width * headerUse.height];
    // read image data from image into BGR array
    for (int i = 0; i < headerUse.height * headerUse.width; i++)
    {
        if (!file1.is_open())
        {
            std::cout << "woops" << std::endl;
        }
        Pixel pxl1, pxl2;
        // Pixel from file1
        file1.read(reinterpret_cast<char *> (&pxl1.Blue), sizeof(pxl1.Blue));
        file1.read(reinterpret_cast<char *> (&pxl1.Green), sizeof(pxl1.Green));
        file1.read(reinterpret_cast<char *> (&pxl1.Red), sizeof(pxl1.Red));
        // Pixel from file2
        file2.read(reinterpret_cast<char *> (&pxl2.Blue), sizeof(pxl2.Blue));
        file2.read(reinterpret_cast<char *> (&pxl2.Green), sizeof(pxl2.Green));
        file2.read(reinterpret_cast<char *> (&pxl2.Red), sizeof(pxl2.Red));
        // screen
        imageData[i] = screen(pxl1, pxl2);
    }
    file1.close();
    file2.close();
    // write header data into output file
    outFile.write(reinterpret_cast<char *> (&headerUse), sizeof(headerUse));
    // write image data into output file
    for (int i = 0; i < headerUse.height * headerUse.width; i++)
    {
        outFile.write(reinterpret_cast<char *> (&imageData[i]), sizeof(imageData[i]));
    }
    outFile.close();
    delete[] imageData;
    headerUse = {};
    headerFiller = {};

    // Part 4 -----------------------------------------------------------------------
    file1.open("input/layer2.tga", std::ios::binary);
    file2.open("input/circles.tga", std::ios::binary);
    outFile.open("output/temp-part4.tga", std::ios::binary);
    // reads header data from images into respective header objects
    file1.read(reinterpret_cast<char *> (&headerUse), 18);
    file2.read(reinterpret_cast<char *> (&headerFiller), 18);
    // create vector for image data
    imageData = new Pixel[headerUse.width * headerUse.height];
    // read image data from image into BGR array
    for (int i = 0; i < headerUse.height * headerUse.width; i++)
    {
        if (!file1.is_open())
        {
            std::cout << "woops" << std::endl;
        }
        Pixel pxl1, pxl2;
        // Pixel from file1
        file1.read(reinterpret_cast<char *> (&pxl1.Blue), sizeof(pxl1.Blue));
        file1.read(reinterpret_cast<char *> (&pxl1.Green), sizeof(pxl1.Green));
        file1.read(reinterpret_cast<char *> (&pxl1.Red), sizeof(pxl1.Red));
        // Pixel from file2
        file2.read(reinterpret_cast<char *> (&pxl2.Blue), sizeof(pxl2.Blue));
        file2.read(reinterpret_cast<char *> (&pxl2.Green), sizeof(pxl2.Green));
        file2.read(reinterpret_cast<char *> (&pxl2.Red), sizeof(pxl2.Red));
        // multiply
        imageData[i] = multiply(pxl1, pxl2);
    }
    file1.close();
    file2.close();
    // write header data into output file
    outFile.write(reinterpret_cast<char *> (&headerUse), sizeof(headerUse));
    // write image data into output file
    for (int i = 0; i < headerUse.height * headerUse.width; i++)
    {
        outFile.write(reinterpret_cast<char *> (&imageData[i]), sizeof(imageData[i]));
    }
    outFile.close();
    delete[] imageData;
    headerUse = {};
    headerFiller = {};

    file1.open("input/pattern2.tga", std::ios::binary);
    file2.open("output/temp-part4.tga", std::ios::binary);
    outFile.open("output/part4.tga", std::ios::binary);
    // reads header data from images into respective header objects
    file1.read(reinterpret_cast<char *> (&headerUse), 18);
    file2.read(reinterpret_cast<char *> (&headerFiller), 18);
    // create vector for image data
    imageData = new Pixel[headerUse.width * headerUse.height];
    // read image data from image into BGR array
    for (int i = 0; i < headerUse.height * headerUse.width; i++)
    {
        if (!file1.is_open())
        {
            std::cout << "woops" << std::endl;
        }
        Pixel pxl1, pxl2;
        // Pixel from file1
        file1.read(reinterpret_cast<char *> (&pxl1.Blue), sizeof(pxl1.Blue));
        file1.read(reinterpret_cast<char *> (&pxl1.Green), sizeof(pxl1.Green));
        file1.read(reinterpret_cast<char *> (&pxl1.Red), sizeof(pxl1.Red));
        // Pixel from file2
        file2.read(reinterpret_cast<char *> (&pxl2.Blue), sizeof(pxl2.Blue));
        file2.read(reinterpret_cast<char *> (&pxl2.Green), sizeof(pxl2.Green));
        file2.read(reinterpret_cast<char *> (&pxl2.Red), sizeof(pxl2.Red));
        // subtract
        imageData[i] = subtract(pxl1, pxl2);
    }
    file1.close();
    file2.close();
    // write header data into output file
    outFile.write(reinterpret_cast<char *> (&headerUse), sizeof(headerUse));
    // write image data into output file
    for (int i = 0; i < headerUse.height * headerUse.width; i++)
    {
        outFile.write(reinterpret_cast<char *> (&imageData[i]), sizeof(imageData[i]));
    }
    outFile.close();
    delete[] imageData;
    headerUse = {};
    headerFiller = {};

    // Part 5 -----------------------------------------------------------------------
    file1.open("input/layer1.tga", std::ios::binary);
    file2.open("input/pattern1.tga", std::ios::binary);
    outFile.open("output/part5.tga", std::ios::binary);
    // reads header data from images into respective header objects
    file1.read(reinterpret_cast<char *> (&headerUse), 18);
    file2.read(reinterpret_cast<char *> (&headerFiller), 18);
    // create vector for image data
    imageData = new Pixel[headerUse.width * headerUse.height];
    // read image data from image into BGR array
    for (int i = 0; i < headerUse.height * headerUse.width; i++)
    {
        if (!file1.is_open())
        {
            std::cout << "woops" << std::endl;
        }
        Pixel pxl1, pxl2;
        // Pixel from file1
        file1.read(reinterpret_cast<char *> (&pxl1.Blue), sizeof(pxl1.Blue));
        file1.read(reinterpret_cast<char *> (&pxl1.Green), sizeof(pxl1.Green));
        file1.read(reinterpret_cast<char *> (&pxl1.Red), sizeof(pxl1.Red));
        // Pixel from file2
        file2.read(reinterpret_cast<char *> (&pxl2.Blue), sizeof(pxl2.Blue));
        file2.read(reinterpret_cast<char *> (&pxl2.Green), sizeof(pxl2.Green));
        file2.read(reinterpret_cast<char *> (&pxl2.Red), sizeof(pxl2.Red));
        // overlay
        imageData[i] = overlay(pxl1, pxl2);
    }
    file1.close();
    file2.close();
    // write header data into output file
    outFile.write(reinterpret_cast<char *> (&headerUse), sizeof(headerUse));
    // write image data into output file
    for (int i = 0; i < headerUse.height * headerUse.width; i++)
    {
        outFile.write(reinterpret_cast<char *> (&imageData[i]), sizeof(imageData[i]));
    }
    outFile.close();
    delete[] imageData;
    headerUse = {};
    headerFiller = {};

    // Part 6 -----------------------------------------------------------------------
    file1.open("input/car.tga", std::ios::binary);
    outFile.open("output/part6.tga", std::ios::binary);
    // reads header data from images into respective header objects
    file1.read(reinterpret_cast<char *> (&headerUse), 18);
    // create vector for image data
    imageData = new Pixel[headerUse.width * headerUse.height];
    // read image data from image into BGR array
    for (int i = 0; i < headerUse.height * headerUse.width; i++)
    {
        if (!file1.is_open())
        {
            std::cout << "woops" << std::endl;
        }
        Pixel pxl1;
        // Pixel from file1
        file1.read(reinterpret_cast<char *> (&pxl1.Blue), sizeof(pxl1.Blue));
        file1.read(reinterpret_cast<char *> (&pxl1.Green), sizeof(pxl1.Green));
        file1.read(reinterpret_cast<char *> (&pxl1.Red), sizeof(pxl1.Red));
        // change Green channel by 200
        // converts 0-255 chars into 0-1 floats
        std::vector<float> Pixel1 = generalizer(pxl1);
        // manipulates Pixel1 and Pixel2 into one PixelFinal
        std::vector<float> screenPixel;
        screenPixel.push_back(std::min(255.0, Pixel1.at(0) * 255 + 0.0));   //Blue
        screenPixel.push_back(std::min(255.0, Pixel1.at(1) * 255 + 200.0)); //Green
        screenPixel.push_back(std::min(255.0, Pixel1.at(2) * 255 + 0.0));   //Red
        // create finalPixel for output
        Pixel finalPixel;
        finalPixel.Blue = static_cast<char>(screenPixel.at(0));
        finalPixel.Green = static_cast<char>(screenPixel.at(1));
        finalPixel.Red = static_cast<char>(screenPixel.at(2));
        imageData[i] = finalPixel;
    }
    file1.close();
    // write header data into output file
    outFile.write(reinterpret_cast<char *> (&headerUse), sizeof(headerUse));
    // write image data into output file
    for (int i = 0; i < headerUse.height * headerUse.width; i++)
    {
        outFile.write(reinterpret_cast<char *> (&imageData[i]), sizeof(imageData[i]));
    }
    outFile.close();
    delete[] imageData;
    headerUse = {};
    headerFiller = {};

    // Part 7 -----------------------------------------------------------------------
    file1.open("input/car.tga", std::ios::binary);
    outFile.open("output/part7.tga", std::ios::binary);
    // reads header data from images into respective header objects
    file1.read(reinterpret_cast<char *> (&headerUse), 18);
    // create vector for image data
    imageData = new Pixel[headerUse.width * headerUse.height];
    // read image data from image into BGR array
    for (int i = 0; i < headerUse.height * headerUse.width; i++)
    {
        if (!file1.is_open())
        {
            std::cout << "woops" << std::endl;
        }
        Pixel pxl1;
        // Pixel from file1
        file1.read(reinterpret_cast<char *> (&pxl1.Blue), sizeof(pxl1.Blue));
        file1.read(reinterpret_cast<char *> (&pxl1.Green), sizeof(pxl1.Green));
        file1.read(reinterpret_cast<char *> (&pxl1.Red), sizeof(pxl1.Red));
        // mult red channel by 4, mult blue channel by 0
        // converts 0-255 chars into 0-1 floats
        std::vector<float> Pixel1 = generalizer(pxl1);
        // manipulates Pixel1 and Pixel2 into one PixelFinal
        std::vector<float> screenPixel;
        screenPixel.push_back(std::min(255.0, Pixel1.at(0) * 0 * 255 + 0.0));
        screenPixel.push_back(std::min(255.0, Pixel1.at(1) * 1 * 255 + 0.0));
        screenPixel.push_back(std::min(255.0, Pixel1.at(2) * 4 * 255 + 0.0));
        // creat finalPixel for output
        Pixel finalPixel;
        finalPixel.Blue = static_cast<char>(screenPixel.at(0));
        finalPixel.Green = static_cast<char>(screenPixel.at(1));
        finalPixel.Red = static_cast<char>(screenPixel.at(2));
        imageData[i] = finalPixel;
    }
    file1.close();
    // write header data into output file
    outFile.write(reinterpret_cast<char *> (&headerUse), sizeof(headerUse));
    // write image data into output file
    for (int i = 0; i < headerUse.height * headerUse.width; i++)
    {
        outFile.write(reinterpret_cast<char *> (&imageData[i]), sizeof(imageData[i]));
    }
    outFile.close();
    delete[] imageData;
    headerUse = {};
    headerFiller = {};

    // Part 8 -----------------------------------------------------------------------
    file1.open("input/car.tga", std::ios::binary);
    outFile.open("output/part8_b.tga", std::ios::binary);
    // reads header data from images into respective header objects
    file1.read(reinterpret_cast<char *> (&headerUse), 18);
    // create vector for image data
    imageData = new Pixel[headerUse.width * headerUse.height];
    // read image data from image into BGR array
    for (int i = 0; i < headerUse.height * headerUse.width; i++)
    {
        if (!file1.is_open())
        {
            std::cout << "woops" << std::endl;
        }
        Pixel pxl1;
        // Pixel from file1
        file1.read(reinterpret_cast<char *> (&pxl1.Blue), sizeof(pxl1.Blue));
        file1.read(reinterpret_cast<char *> (&pxl1.Green), sizeof(pxl1.Green));
        file1.read(reinterpret_cast<char *> (&pxl1.Red), sizeof(pxl1.Red));
        // isolates blue channel
        // converts 0-255 chars into 0-1 floats
        std::vector<float> Pixel1 = generalizer(pxl1);
        // manipulates Pixel1 and Pixel2 into one PixelFinal
        std::vector<float> screenPixel;
        screenPixel.push_back(std::min(255.0, Pixel1.at(0) * 255 + 0.0));
        // creat finalPixel for output
        Pixel finalPixel;
        finalPixel.Blue = static_cast<char>(screenPixel.at(0));
        finalPixel.Green = static_cast<char>(screenPixel.at(0));
        finalPixel.Red = static_cast<char>(screenPixel.at(0));
        imageData[i] = finalPixel;
    }
    file1.close();
    // write header data into output file
    outFile.write(reinterpret_cast<char *> (&headerUse), sizeof(headerUse));
    // write image data into output file
    for (int i = 0; i < headerUse.height * headerUse.width; i++)
    {
        outFile.write(reinterpret_cast<char *> (&imageData[i]), sizeof(imageData[i]));
    }
    outFile.close();
    delete[] imageData;
    headerUse = {};
    headerFiller = {};

    file1.open("input/car.tga", std::ios::binary);
    outFile.open("output/part8_g.tga", std::ios::binary);
    // reads header data from images into respective header objects
    file1.read(reinterpret_cast<char *> (&headerUse), 18);
    // create vector for image data
    imageData = new Pixel[headerUse.width * headerUse.height];
    // read image data from image into BGR array
    for (int i = 0; i < headerUse.height * headerUse.width; i++)
    {
        if (!file1.is_open())
        {
            std::cout << "woops" << std::endl;
        }
        Pixel pxl1;
        // Pixel from file1
        file1.read(reinterpret_cast<char *> (&pxl1.Blue), sizeof(pxl1.Blue));
        file1.read(reinterpret_cast<char *> (&pxl1.Green), sizeof(pxl1.Green));
        file1.read(reinterpret_cast<char *> (&pxl1.Red), sizeof(pxl1.Red));
        // isolates green channel
        // converts 0-255 chars into 0-1 floats
        std::vector<float> Pixel1 = generalizer(pxl1);
        // manipulates Pixel1 and Pixel2 into one PixelFinal
        std::vector<float> screenPixel;
        screenPixel.push_back(std::min(255.0, Pixel1.at(1) * 255 + 0.0));
        // creat finalPixel for output
        Pixel finalPixel;
        finalPixel.Blue = static_cast<char>(screenPixel.at(0));
        finalPixel.Green = static_cast<char>(screenPixel.at(0));
        finalPixel.Red = static_cast<char>(screenPixel.at(0));
        imageData[i] = finalPixel;
    }
    file1.close();
    // write header data into output file
    outFile.write(reinterpret_cast<char *> (&headerUse), sizeof(headerUse));
    // write image data into output file
    for (int i = 0; i < headerUse.height * headerUse.width; i++)
    {
        outFile.write(reinterpret_cast<char *> (&imageData[i]), sizeof(imageData[i]));
    }
    outFile.close();
    delete[] imageData;
    headerUse = {};
    headerFiller = {};

    file1.open("input/car.tga", std::ios::binary);
    outFile.open("output/part8_r.tga", std::ios::binary);
    // reads header data from images into respective header objects
    file1.read(reinterpret_cast<char *> (&headerUse), 18);
    // create vector for image data
    imageData = new Pixel[headerUse.width * headerUse.height];
    // read image data from image into BGR array
    for (int i = 0; i < headerUse.height * headerUse.width; i++)
    {
        if (!file1.is_open())
        {
            std::cout << "woops" << std::endl;
        }
        Pixel pxl1;
        // Pixel from file1
        file1.read(reinterpret_cast<char *> (&pxl1.Blue), sizeof(pxl1.Blue));
        file1.read(reinterpret_cast<char *> (&pxl1.Green), sizeof(pxl1.Green));
        file1.read(reinterpret_cast<char *> (&pxl1.Red), sizeof(pxl1.Red));
        // isolates red channel
        // converts 0-255 chars into 0-1 floats
        std::vector<float> Pixel1 = generalizer(pxl1);
        // manipulates Pixel1 and Pixel2 into one PixelFinal
        std::vector<float> screenPixel;
        screenPixel.push_back(std::min(255.0, Pixel1.at(2) * 255 + 0.0));
        // creat finalPixel for output
        Pixel finalPixel;
        finalPixel.Blue = static_cast<char>(screenPixel.at(0));
        finalPixel.Green = static_cast<char>(screenPixel.at(0));
        finalPixel.Red = static_cast<char>(screenPixel.at(0));
        imageData[i] = finalPixel;
    }
    file1.close();
    // write header data into output file
    outFile.write(reinterpret_cast<char *> (&headerUse), sizeof(headerUse));
    // write image data into output file
    for (int i = 0; i < headerUse.height * headerUse.width; i++)
    {
        outFile.write(reinterpret_cast<char *> (&imageData[i]), sizeof(imageData[i]));
    }
    outFile.close();
    delete[] imageData;
    headerUse = {};
    headerFiller = {};

    // Part 9 -----------------------------------------------------------------------
    file1.open("input/layer_red.tga", std::ios::binary);
    file2.open("input/layer_green.tga", std::ios::binary);
    file3.open("input/layer_blue.tga", std::ios::binary);
    outFile.open("output/part9.tga", std::ios::binary);
    // reads header data from images into respective header objects
    file1.read(reinterpret_cast<char *> (&headerUse), 18);
    file2.read(reinterpret_cast<char *> (&headerFiller), 18);
    headerFiller = {};
    file3.read(reinterpret_cast<char *> (&headerFiller), 18);
    // create vector for image data
    imageData = new Pixel[headerUse.width * headerUse.height];
    // read image data from image into BGR array
    for (int i = 0; i < headerUse.height * headerUse.width; i++)
    {
        if (!file1.is_open())
        {
            std::cout << "woops" << std::endl;
        }
        Pixel pxl1, pxl2, pxl3;
        // read red layer from file 1
        file1.read(reinterpret_cast<char *> (&pxl1.Blue), sizeof(pxl1.Blue));
        file1.read(reinterpret_cast<char *> (&pxl1.Green), sizeof(pxl1.Green));
        file1.read(reinterpret_cast<char *> (&pxl1.Red), sizeof(pxl1.Red));
        // read green layer from file 2
        file2.read(reinterpret_cast<char *> (&pxl2.Blue), sizeof(pxl2.Blue));
        file2.read(reinterpret_cast<char *> (&pxl2.Green), sizeof(pxl2.Green));
        file2.read(reinterpret_cast<char *> (&pxl2.Red), sizeof(pxl2.Red));
        // read blue layer from file 3
        file3.read(reinterpret_cast<char *> (&pxl3.Blue), sizeof(pxl3.Blue));
        file3.read(reinterpret_cast<char *> (&pxl3.Green), sizeof(pxl3.Green));
        file3.read(reinterpret_cast<char *> (&pxl3.Red), sizeof(pxl3.Red));

        // converts 0-255 chars into 0-1 floats
        std::vector<float> Pixel1 = generalizer(pxl1);
        std::vector<float> Pixel2 = generalizer(pxl2);
        std::vector<float> Pixel3 = generalizer(pxl3);
        // manipulates Pixel1 and Pixel2 into one PixelFinal
        std::vector<float> screenPixel;
        screenPixel.push_back(std::min(255.0, Pixel3.at(0) * 255 + 0.0)); // Blue
        screenPixel.push_back(std::min(255.0, Pixel2.at(0) * 255 + 0.0)); // Green
        screenPixel.push_back(std::min(255.0, Pixel1.at(0) * 255 + 0.0)); // Red
        // creat finalPixel for output
        Pixel finalPixel;
        finalPixel.Blue = static_cast<char>(screenPixel.at(0));
        finalPixel.Green = static_cast<char>(screenPixel.at(1));
        finalPixel.Red = static_cast<char>(screenPixel.at(2));
        imageData[i] = finalPixel;
    }
    file1.close();
    file2.close();
    file3.close();
    // write header data into output file
    outFile.write(reinterpret_cast<char *> (&headerUse), sizeof(headerUse));
    // write image data into output file
    for (int i = 0; i < headerUse.height * headerUse.width; i++)
    {
        outFile.write(reinterpret_cast<char *> (&imageData[i]), sizeof(imageData[i]));
    }
    outFile.close();
    delete[] imageData;
    headerUse = {};
    headerFiller = {};

    // Part 10 -----------------------------------------------------------------------
    file1.open("input/text2.tga", std::ios::binary);
    outFile.open("output/part10.tga", std::ios::binary);
    // reads header data from images into respective header objects
    file1.read(reinterpret_cast<char *> (&headerUse), 18);
    // create vector for image data
    imageData = new Pixel[headerUse.width * headerUse.height];
    // read image data from image into BGR array
    for (int i = 0; i < headerUse.height * headerUse.width; i++)
    {
        if (!file1.is_open())
        {
            std::cout << "woops" << std::endl;
        }
        Pixel pxl1;
        // Pixel from file1
        file1.read(reinterpret_cast<char *> (&pxl1.Blue), sizeof(pxl1.Blue));
        file1.read(reinterpret_cast<char *> (&pxl1.Green), sizeof(pxl1.Green));
        file1.read(reinterpret_cast<char *> (&pxl1.Red), sizeof(pxl1.Red));
        // rotate 180 degrees
        imageData[(headerUse.height * headerUse.width) - 1 - i] = pxl1;
    }
    file1.close();
    // write header data into output file
    outFile.write(reinterpret_cast<char *> (&headerUse), sizeof(headerUse));
    // write image data into output file
    for (int i = 0; i < headerUse.height * headerUse.width; i++)
    {
        outFile.write(reinterpret_cast<char *> (&imageData[i]), sizeof(imageData[i]));
    }
    outFile.close();
    delete[] imageData;
    headerUse = {};

    // EXTRA CREDIT -----------------------------------------------------------------------
    file1.open("input/text.tga", std::ios::binary);
    file2.open("input/pattern1.tga", std::ios::binary);
    file3.open("input/car.tga", std::ios::binary);
    file4.open("input/circles.tga", std::ios::binary);
    outFile.open("output/extracredit.tga", std::ios::binary);
    // reads header data from images into respective header objects
    file1.read(reinterpret_cast<char *> (&headerUse), 18);
    file2.read(reinterpret_cast<char *> (&headerFiller), 18);
    headerFiller = {};
    file3.read(reinterpret_cast<char *> (&headerUse), 18);
    headerFiller = {};
    file4.read(reinterpret_cast<char *> (&headerFiller), 18);
    // updates height and width for the expanded image
    headerUse.height = headerUse.height * 2;
    headerUse.width = headerUse.width * 2;
    // create vector for image data
    imageData = new Pixel[headerUse.width * headerUse.height];
    // read image data from image into BGR array
    short count = 0;
    short quadrant = 1;
    for (int i = 0; i < headerUse.height * headerUse.width; i++)
    {
        if (!file1.is_open())
        {
            std::cout << "woops" << std::endl;
        }
        Pixel pxl1, pxl2, pxl3, pxl4;
        // Read into imageData
        /*
         * Quadrants
         * | 3 | 4 |
         * | 1 | 2 |
         */
        if (i < 1024 * 512) // quadrant 0 and 1
        {
            if (quadrant == 1 && count < 512)
            {
                file1.read(reinterpret_cast<char *> (&pxl1.Blue), sizeof(pxl1.Blue));
                file1.read(reinterpret_cast<char *> (&pxl1.Green), sizeof(pxl1.Green));
                file1.read(reinterpret_cast<char *> (&pxl1.Red), sizeof(pxl1.Red));
                imageData[i] = pxl1;
                count++;
            }
            else if (quadrant == 1 && count == 512) // move to quadrant 2
            {
                file2.read(reinterpret_cast<char *> (&pxl2.Blue), sizeof(pxl2.Blue));
                file2.read(reinterpret_cast<char *> (&pxl2.Green), sizeof(pxl2.Green));
                file2.read(reinterpret_cast<char *> (&pxl2.Red), sizeof(pxl2.Red));
                quadrant = 2;
                imageData[i] = pxl2;
                count = 1;
            }
            else if (quadrant == 2 && count < 512)
            {
                file2.read(reinterpret_cast<char *> (&pxl2.Blue), sizeof(pxl2.Blue));
                file2.read(reinterpret_cast<char *> (&pxl2.Green), sizeof(pxl2.Green));
                file2.read(reinterpret_cast<char *> (&pxl2.Red), sizeof(pxl2.Red));
                imageData[i] = pxl2;
                count++;
            }
            else if (quadrant == 2 && count == 512) // move back to quadrant 1
            {
                file1.read(reinterpret_cast<char *> (&pxl1.Blue), sizeof(pxl1.Blue));
                file1.read(reinterpret_cast<char *> (&pxl1.Green), sizeof(pxl1.Green));
                file1.read(reinterpret_cast<char *> (&pxl1.Red), sizeof(pxl1.Red));
                quadrant = 1;
                imageData[i] = pxl1;
                count = 1;
            }
            else
            {
                std::cout << "\nquadrant: " << quadrant << "\ncount: " << count << std::endl;
            }
        }
        else if (quadrant == 2 && count != 0)
        {
            file3.read(reinterpret_cast<char *> (&pxl3.Blue), sizeof(pxl3.Blue));
            file3.read(reinterpret_cast<char *> (&pxl3.Green), sizeof(pxl3.Green));
            file3.read(reinterpret_cast<char *> (&pxl3.Red), sizeof(pxl3.Red));
            quadrant = 3;
            imageData[i] = pxl3;
            count = 1;
        }
        else // quadrant 2 and 3
        {
            if (quadrant == 3 && count < 512)
            {
                file3.read(reinterpret_cast<char *> (&pxl3.Blue), sizeof(pxl3.Blue));
                file3.read(reinterpret_cast<char *> (&pxl3.Green), sizeof(pxl3.Green));
                file3.read(reinterpret_cast<char *> (&pxl3.Red), sizeof(pxl3.Red));
                imageData[i] = pxl3;
                count++;
            }
            else if (quadrant == 3 && count == 512) // move to quadrant 4
            {
                file4.read(reinterpret_cast<char *> (&pxl4.Blue), sizeof(pxl4.Blue));
                file4.read(reinterpret_cast<char *> (&pxl4.Green), sizeof(pxl4.Green));
                file4.read(reinterpret_cast<char *> (&pxl4.Red), sizeof(pxl4.Red));
                quadrant = 4;
                imageData[i] = pxl4;
                count = 1;
            }
            else if (quadrant == 4 && count < 512)
            {
                file4.read(reinterpret_cast<char *> (&pxl4.Blue), sizeof(pxl4.Blue));
                file4.read(reinterpret_cast<char *> (&pxl4.Green), sizeof(pxl4.Green));
                file4.read(reinterpret_cast<char *> (&pxl4.Red), sizeof(pxl4.Red));
                imageData[i] = pxl4;
                count++;
            }
            else if (quadrant == 4 && count == 512) // move back to quadrant 3
            {
                file3.read(reinterpret_cast<char *> (&pxl3.Blue), sizeof(pxl3.Blue));
                file3.read(reinterpret_cast<char *> (&pxl3.Green), sizeof(pxl3.Green));
                file3.read(reinterpret_cast<char *> (&pxl3.Red), sizeof(pxl3.Red));
                quadrant = 3;
                imageData[i] = pxl3;
                count = 1;
            }
            else
            {
                std::cout << "\nquadrant: " << quadrant << "\ncount: " << count << std::endl;
            }
        }
    }
    file1.close();
    file2.close();
    file3.close();
    file4.close();
    // write header data into output file
    outFile.write(reinterpret_cast<char *> (&headerUse), sizeof(headerUse));
    // write image data into output file
    for (int i = 0; i < headerUse.height * headerUse.width; i++)
    {
        outFile.write(reinterpret_cast<char *> (&imageData[i]), sizeof(imageData[i]));
    }
    outFile.close();
    delete[] imageData;
    headerUse = {};
    headerFiller = {};

    // TESTING METHODS ---------------------------------------------------------------

    // Part 1
    /*
    std::ifstream myFile, exampleFile;
    exampleFile.open("examples/EXAMPLE_part1.tga", std::ios::binary);
    myFile.open("output/part1.tga", std::ios::binary);
    std::cout << "Test #1" << std::flush;
    if (tester(myFile, exampleFile))
    {
        std::cout << " Passed!" << std::endl;
    }
    else
    {
        std::cout << " Failed!" << std::endl;
    }
    exampleFile.close();
    myFile.close();

    // Part 2
    exampleFile.open("examples/EXAMPLE_part2.tga", std::ios::binary);
    myFile.open("output/part2.tga", std::ios::binary);
    std::cout << "Test #2" << std::flush;
    if (tester(myFile, exampleFile))
    {
        std::cout << " Passed!" << std::endl;
    }
    else
    {
        std::cout << " Failed!" << std::endl;
    }
    exampleFile.close();
    myFile.close();

    // Part 3
    exampleFile.open("examples/EXAMPLE_part3.tga", std::ios::binary);
    myFile.open("output/part3.tga", std::ios::binary);
    std::cout << "Test #3" << std::flush;
    if (tester(myFile, exampleFile))
    {
        std::cout << " Passed!" << std::endl;
    }
    else
    {
        std::cout << " Failed!" << std::endl;
    }
    exampleFile.close();
    myFile.close();

    // Part 4
    exampleFile.open("examples/EXAMPLE_part4.tga", std::ios::binary);
    myFile.open("output/part4.tga", std::ios::binary);
    std::cout << "Test #4" << std::flush;
    if (tester(myFile, exampleFile))
    {
        std::cout << " Passed!" << std::endl;
    }
    else
    {
        std::cout << " Failed!" << std::endl;
    }
    exampleFile.close();
    myFile.close();

    // Part 5
    exampleFile.open("examples/EXAMPLE_part5.tga", std::ios::binary);
    myFile.open("output/part5.tga", std::ios::binary);
    std::cout << "Test #5" << std::flush;
    if (tester(myFile, exampleFile))
    {
        std::cout << " Passed!" << std::endl;
    }
    else
    {
        std::cout << " Failed!" << std::endl;
    }
    exampleFile.close();
    myFile.close();

    // Part 6
    exampleFile.open("examples/EXAMPLE_part6.tga", std::ios::binary);
    myFile.open("output/part6.tga", std::ios::binary);
    std::cout << "Test #6" << std::flush;
    if (tester(myFile, exampleFile))
    {
        std::cout << " Passed!" << std::endl;
    }
    else
    {
        std::cout << " Failed!" << std::endl;
    }
    exampleFile.close();
    myFile.close();

    // Part 7
    exampleFile.open("examples/EXAMPLE_part7.tga", std::ios::binary);
    myFile.open("output/part7.tga", std::ios::binary);
    std::cout << "Test #7" << std::flush;
    if (tester(myFile, exampleFile))
    {
        std::cout << " Passed!" << std::endl;
    }
    else
    {
        std::cout << " Failed!" << std::endl;
    }
    exampleFile.close();
    myFile.close();

    // Part 8
    exampleFile.open("examples/EXAMPLE_part8.tga", std::ios::binary);
    myFile.open("output/part8.tga", std::ios::binary);
    std::cout << "Test #8" << std::flush;
    if (tester(myFile, exampleFile))
    {
        std::cout << " Passed!" << std::endl;
    }
    else
    {
        std::cout << " Failed!" << std::endl;
    }
    exampleFile.close();
    myFile.close();

    // Part 9
    exampleFile.open("examples/EXAMPLE_part9.tga", std::ios::binary);
    myFile.open("output/part9.tga", std::ios::binary);
    std::cout << "Test #9" << std::flush;
    if (tester(myFile, exampleFile))
    {
        std::cout << " Passed!" << std::endl;
    }
    else
    {
        std::cout << " Failed!" << std::endl;
    }
    exampleFile.close();
    myFile.close();

    // Part 10
    exampleFile.open("examples/EXAMPLE_part10.tga", std::ios::binary);
    myFile.open("output/part10.tga", std::ios::binary);
    std::cout << "Test #10" << std::flush;
    if (tester(myFile, exampleFile))
    {
        std::cout << " Passed!" << std::endl;
    }
    else
    {
        std::cout << " Failed!" << std::endl;
    }
    exampleFile.close();
    myFile.close();
    */

    return 0;
}
