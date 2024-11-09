
#ifndef IMAGE_H
#define IMAGE_H

class Image
{
    unsigned char* image;
    unsigned char* pixelData;
public:
    explicit Image(unsigned char* imageData);
    unsigned char* getImageData();
    unsigned char* getPixelData();
    unsigned char getWidth();
    unsigned char getHeight();
    void setImageData(unsigned char* newData);
};

#endif //IMAGE_H
