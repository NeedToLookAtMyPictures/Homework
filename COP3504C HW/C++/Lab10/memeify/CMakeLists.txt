cmake_minimum_required(VERSION 3.5.0)
project(memeify VERSION 0.1.0 LANGUAGES C CXX)

set(SFML_DIR "C:/Libraries/SFML-2.5.1/lib/cmake/SFML") # add your dir path
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)



add_executable(lab10 main.cpp memer.cpp)
target_link_libraries(lab10 sfml-graphics sfml-audio)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)