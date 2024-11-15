#include <string>
#include "Cow.h"

Cow::Cow (const std::string& _name)
{
    this->name = _name;
}

void Cow::setImage(const std::string& _image)
{
    this->image = _image;
}
