// thanks to Kiran and Ryan for the pragma use advice, made file-reading much easier
#ifndef HEADER_H
#define HEADER_H

#pragma pack(push, 1)

struct Header
{
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
};

#pragma pack(pop)

#endif //HEADER_H
