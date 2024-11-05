#ifndef COW_H
#define COW_H
#include <string>

class Cow
{
public:
    std::string image;
    std::string name;
    Cow(const std::string& _name);
    std::string& getImage()
    {
        return image;
    };
    std::string& getName()
    {
        return name;
    };
    virtual void setImage(const std::string& _image);
};

#endif //COW_H
