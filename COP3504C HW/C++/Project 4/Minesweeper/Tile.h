#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include <array>

class Tile{
public:
    enum State { REVEALED, HIDDEN, FLAGGED, EXPLODED }; // Represents tile’s current UI state (visualization).
    Tile(sf::Vector2f _position); // Constructs a new tile object at the designated _position.
    sf::Vector2f getLocation(); // Returns the position of this tile.
    inline State getState() { return tileStatus; } // Returns current state of this tile.
    std::array<Tile*, 8>& getNeighbors(); // Returns pointer to array of Tile pointers (see Figure 2 for ordering).
    void setState(State _state); // Sets the state of this tile. Should trigger other behaviors related to the state change (including visualization).
    void setNeighbors(std::array<Tile*, 8> _neighbors); // Populates / replaces the neighboring tile container.
    void onClickLeft(); // Defines the reveal behavior for a tile when the left mouse button is clicked inside its boundaries.
    void onClickRight(); // Toggles this tile’s state between FLAGGED and HIDDEN.
    void draw(); // Creates a sprite of this tile according to its state.
protected:
    void revealNeighbors(); // Based on State and mine content of the tile neighbors, set their state to REVEALED.
private:
    void setMine() { mineStatus = true; } // identifies tile as a mine
    bool isMine() { return mineStatus; } // returns true if tile is a mine, false otherwise
    sf::Sprite sprite;
    sf::Sprite sprite2;
    std::array<Tile*, 8> neighbors;
    bool mineStatus = false;
    State tileStatus = HIDDEN;
    sf::Vector2f position;

friend class minesweeper;
friend class Toolbox;
friend class GameState;
};

#endif //TILE_H
