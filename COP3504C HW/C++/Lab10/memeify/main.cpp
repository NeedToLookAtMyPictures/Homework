#include <iostream>
#include "memer.h"

int main(int argc, char *argv[])
{
    sf::Image img;
    img.loadFromFile("./doge.jpg");
    sf::String topText = argv[3];
    sf::String bottomText = "";
    int topX = 240;
    int topY = 160;
    int bottomX = 240;
    int bottomY = 320;
    if(argc > 4)
    {
        bottomText = argv[4];
        if (argc > 5)
        {
            topX = atoi(argv[5]);
            if (argc > 6)
            {
                topY = atoi(argv[6]);
                if (argc > 7)
                {
                    bottomX = atoi(argv[7]);
                    if (argc > 8)
                    {
                        bottomY = atoi(argv[8]);
                    }
                }
            }
        }
    }

    try
    {
        generateMeme(img, topText, bottomText, topX, topY, bottomX, bottomY);
    }
    catch (std::runtime_error oops)
    {
        std::cout << oops.what() << std::endl;
    }
    return 0;
}
