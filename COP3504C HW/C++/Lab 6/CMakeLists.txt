cmake_minimum_required(VERSION 3.29)
project(Lab_6)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lab_6 ConsoleGfx.cpp scaler.cpp Image.cpp)
