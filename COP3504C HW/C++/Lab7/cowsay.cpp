#include <iostream>
#include <string>
#include "HeiferGenerator.h"

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        return 1;
    }
    auto cows = HeiferGenerator::getCows();
    //0 == heifer
    //1 == kitteh
    //2 == dragon
    //3 == icedragon
    std::string argv1 = argv[1];
    if (argv1 == "-l")
    {
        //List available cows
        std::cout << "Cows available: heifer kitteh dragon ice-dragon\n" << std::endl;
    }
    else if (argv1 == "-n")
    {
        //Print message using animal following -n
        //Need to check that animal following -n is valid
        std::string argv2 = argv[2];
        if (argv2 == "heifer" || argv2 == "kitteh" || argv2 == "dragon" || argv2 == "ice-dragon")
        {
            std::string message;
            for (int i = 3; i < argc; i++)
            {
                //Concatenate the message following "-n [cow] ____"
                message += argv[i];
                if (i != argc - 1)
                {
                    message += " ";
                }
            }
            std::cout << "\n" << message << std::endl;

            //Print cow based on argv[2]
            if (argv2 == "heifer")
            {
                std::cout << cows[0]->getImage() << std::endl;
            }
            else if (argv2 == "kitteh")
            {
                std::cout << cows[1]->getImage() << std::endl;
            }
            else if (argv2 == "dragon")
            {
                std::cout << cows[2]->getImage() << std::endl;
                std::cout << "This dragon can breathe fire.\n" << std::endl;
            }
            else
            {
                std::cout << cows[3]->getImage() << std::endl;
                std::cout << "This dragon cannot breathe fire.\n" << std::endl;
            }

        }
        else
        {
            std::cout << "Could not find " << argv2 << " cow!\n" << std::endl;
        }
    }
    else
    {
        //Print message using default cow
        std::string message;
        for (int i = 1; i < argc; i++)
        {   //Concatenate the message following .\Lab7.exe
            message += argv[i];
            if (i != argc - 1)
            {
                message += " ";
            }
        }

        //Print message and then cow underneath it
        std::cout << "\n" << message << std::endl;
        std::cout << cows[0]->getImage() << std::endl;
    }

    return 0;

}