// Inherits from Dragon
#include "IceDragon.h"
#include <string>

IceDragon::IceDragon(const std::string& _name, const std::string& _image) : Dragon(_name, _image){};

bool IceDragon::canBreatheFire()
{
    return false;
}