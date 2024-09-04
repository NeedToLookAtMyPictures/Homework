#include "helpers.h"
#include "math.h"

// Convert image to grayscale, average the three RGB values together and apply that value to all RGB values equally -------------
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0, avg = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            avg = image[h][w].rgbtRed + image[h][w].rgbtGreen + image[h][w].rgbtBlue;
            avg = (int) round(avg / 3.0);
            image[h][w].rgbtRed = avg;
            image[h][w].rgbtGreen = avg;
            image[h][w].rgbtBlue = avg;
        }
        avg = 0;
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int originalRed, originalGreen, originalBlue;
    int sepiaRed, sepiaGreen, sepiaBlue;
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            originalRed = image[h][w].rgbtRed;
            originalGreen = image[h][w].rgbtGreen;
            originalBlue = image[h][w].rgbtBlue;
            sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            if (sepiaRed > 255)
            {
                image[h][w].rgbtRed = 255;
            }
            else
            {
                image[h][w].rgbtRed = sepiaRed;
            }
            sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            if (sepiaGreen > 255)
            {
                image[h][w].rgbtGreen = 255;
            }
            else
            {
                image[h][w].rgbtGreen = sepiaGreen;
            }
            sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            if (sepiaBlue > 255)
            {
                image[h][w].rgbtBlue = 255;
            }
            else
            {
                image[h][w].rgbtBlue = sepiaBlue;
            }
        }
    }
    return;
}

// Reflect image horizontally, reverse the order of the bytes
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int tempRed, tempGreen, tempBlue = 0;
    int midWidth = width / 2;
    for (int h = 0; h < height; h++) // go half way
    {
        for (int w = 0; w < midWidth; w++)
        {
            // store the leftside pixel's values away in temp values
            tempRed = image[h][w].rgbtRed;
            tempGreen = image[h][w].rgbtGreen;
            tempBlue = image[h][w].rgbtBlue;

            image[h][w].rgbtRed = image[h][width - w - 1].rgbtRed;
            image[h][w].rgbtGreen = image[h][width - w - 1].rgbtGreen;
            image[h][w].rgbtBlue = image[h][width - w - 1].rgbtBlue;

            image[h][width - w - 1].rgbtRed = tempRed;
            image[h][width - w - 1].rgbtGreen = tempGreen;
            image[h][width - w - 1].rgbtBlue = tempBlue;
        }
    }
    return;
}

// Blur image, averge the value of all of the RGB bytes 1 column and 1 row from each other
void blur(int height, int width, RGBTRIPLE image[height][width])
{
   RGBTRIPLE temp[height][width];

   for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int total_Red, total_Blue, total_Green;
            total_Red = total_Blue = total_Green = 0;
            float counter = 0.00;
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    int currentX = i + x;
                    int currentY = j + y;

                    if (currentX < 0 || currentX > (height - 1) || currentY < 0 || currentY > (width - 1))
                    {
                        continue;
                    }

                    //Get the image value
                    total_Red += image[currentX][currentY].rgbtRed;
                    total_Green += image[currentX][currentY].rgbtGreen;
                    total_Blue += image[currentX][currentY].rgbtBlue;

                    counter++;
                }

                //do the average of neigbhouring pexels
                temp[i][j].rgbtRed = round(total_Red / counter);
                temp[i][j].rgbtGreen = round(total_Green / counter);
                temp[i][j].rgbtBlue = round(total_Blue / counter);
            }
        }

    }

    //copy the blurr image to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }
    return;
}
