#ifndef ICEDRAGON_H
#define ICEDRAGON_H
#include "Dragon.h"
#include <string>

class IceDragon : public Dragon
{
public:
    IceDragon(const std::string& _name, const std::string& _image);
    bool canBreatheFire();
};

#endif //ICEDRAGON_H

