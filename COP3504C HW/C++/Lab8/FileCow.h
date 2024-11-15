#ifndef FILECOW_H
#define FILECOW_H
#include <string>
#include "Cow.h"

class FileCow : public Cow
{
public:
    FileCow(const std::string& _name, const std::string& filename);
    void setImage();
};

#endif //FILECOW_H
