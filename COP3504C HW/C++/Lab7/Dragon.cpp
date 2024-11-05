// Inherits from Cow
#include "Dragon.h"
#include <string>

Dragon::Dragon(const std::string& _name, const std::string& _image): Cow(_name)
{
    image = _image;
};

bool Dragon::canBreatheFire()
{
    return true;
};