#ifndef DRAGON_H
#define DRAGON_H
#include "Cow.h"
#include <string>

class Dragon : public Cow
{
public:
    Dragon(const std::string& _name, const std::string& _image);
    bool canBreatheFire();
};

#endif //DRAGON_H

