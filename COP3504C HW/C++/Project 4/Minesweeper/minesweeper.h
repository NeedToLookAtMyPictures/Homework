#ifndef MINESWEEPER_H
#define MINESWEEPER_H

void restart();

void render();

void toggleDebugMode();
bool getDebugMode();

inline int launch()
  {
    // This method is invoked directly by main() and is responsible for the game’s launch. It should be possible to
    // directly invoke this function after including the submitted source and header files in the test suite.
    restart();
    render();
    return 1;
  }

int main();


#endif //MINESWEEPER_H
