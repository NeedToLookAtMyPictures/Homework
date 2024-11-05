cmake_minimum_required(VERSION 3.29)
project(Lab7)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(Lab7 HeiferGenerator.cpp Cow.cpp Dragon.cpp IceDragon.cpp cowsay.cpp)
