cmake_minimum_required(VERSION 3.29)
project(Lab8)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(Lab8 cowsay.cpp HeiferGenerator.h HeiferGenerator.cpp Cow.h Cow.cpp Dragon.h Dragon.cpp IceDragon.h IceDragon.cpp FileCow.h FileCow.cpp)