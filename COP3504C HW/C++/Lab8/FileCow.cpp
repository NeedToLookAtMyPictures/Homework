#include <fstream>
#include <string>
#include <iostream>
#include "FileCow.h"

FileCow::FileCow(const std::string& _name, const std::string& filename) : Cow(_name)
{
  std::ifstream file(filename);
   if (!file.is_open())
     {
     throw std::ifstream::failure("MOOOOO!!!!!!");
     }

  std::string _image = "";
  std::string line;
  while (std::getline(file, line))
  {
    _image += line;
    _image += "\n";
  }
  this->image = _image;
}

void FileCow::setImage()
{
  throw std::runtime_error("Cannot reset FileCow Image");
}