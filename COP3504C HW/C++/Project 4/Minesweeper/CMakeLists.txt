cmake_minimum_required(VERSION 3.5.0)
project(Minesweeper VERSION 0.1.0 LANGUAGES C CXX)

set(SFML_DIR "C:/Libraries/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)



add_executable(Minesweeper minesweeper.cpp Button.cpp GameState.cpp Tile.cpp Toolbox.cpp)
target_link_libraries(Minesweeper sfml-graphics sfml-audio)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)