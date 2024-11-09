#include "Image.h"
#include <iostream>

Image::Image(unsigned char* imageData)
{
    // Argument is a pointer to an array of raw image data as loaded from the file.
    // array format: WIDTH (1 byte), HEIGHT (1 byte), PIXEL DATA ([WIDTH * HEIGHT] bytes)
    this->image = imageData;
}

unsigned char* Image::getImageData()
{
    // Returns a pointer to the raw image data (not a copy)
    return this->image;
}

unsigned char* Image::getPixelData()
{
    // Returns a pointer to the raw pixel data (excluding the image property information). Should not be a copy
    // index 0 and 1 hold width and height of the image, respectively, index 2 is where pixel data begins
    return &this->image[2];
}

unsigned char Image::getWidth()
{
    // Returns the width of the image
    unsigned char width = this->image[0];
    return width;
}

unsigned char Image::getHeight()
{
    // Returns the height of the image
    unsigned char height = this->image[1];
    return height;
}

void Image::setImageData(unsigned char* newData)
{
    // Changes the image data to the new pointer
    this->image = newData;
}
