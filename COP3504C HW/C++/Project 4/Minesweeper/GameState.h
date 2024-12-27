#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Tile.h"
#include <memory>
class Tile;
class GameState{
public:
    enum PlayStatus { WIN, LOSS, PLAYING }; // Tracks the play status of the game, which is reflected in the behavior of the user interface and visualizations.
    GameState(sf::Vector2i _dimensions = sf::Vector2i(25, 16), int _numberOfMines = 50); // Constructs a new random game state with specified tile _dimensions and the specified _numberOfMines.
    GameState(const char* filepath); // Constructs a game state based on the size, mine placement, and mine number specified at filepath.
    int getFlagCount(); // Current count of the number of flags placed on the screen.
    inline int getMineCount() { return numberOfMines; } // Current count of the number of mines actually on the board.
    Tile* getTile(int x, int y); // Returns a pointer to the Tile at the specified coordinates, or nullptr if out of bounds.
    inline PlayStatus getPlayStatus()
    {
        // Returns the play status of the game.
        return GameStatus;
    }
    void setPlayStatus(PlayStatus _status); // Sets the play status of the game.
private:
    bool lost = false;
    std::vector<std::shared_ptr<Tile>> tiles;
    std::vector<std::vector<int>> board;
    int flagCount = 0;
    PlayStatus GameStatus = PLAYING;
    int numberOfMines;

friend class Toolbox;
friend class Tile;
};
#endif //GAMESTATE_H
