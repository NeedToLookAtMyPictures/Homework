#include "Tile.h"
#include "Toolbox.h"
#include "GameState.h"
#include "minesweeper.h"

Tile::Tile(sf::Vector2f _position)
{
    // Constructs a new tile object at the designated _position
    Toolbox& tools = Toolbox::getInstance();
    position = _position;
}
sf::Vector2f Tile::getLocation()
{
    // Returns the position of this tile.
    return position;
}
std::array<Tile*, 8>& Tile::getNeighbors()
{
    // Returns pointer to array of Tile pointers (see Figure 2 for ordering).
    return neighbors;
}
void Tile::setState(State _state)
{
    // Sets the state of this tile. Should trigger other behaviors related to the state change (including visualization).
    Toolbox& tools = Toolbox::getInstance();
    tileStatus = _state;
    if(isMine() && _state == REVEALED)
    {
        tileStatus = EXPLODED;
        if (tools.gameState->getPlayStatus() != GameState::LOSS)
        {
            tools.gameState->lost = true;
            tools.gameState->setPlayStatus(GameState::LOSS);
        }
    }
}
void Tile::setNeighbors(std::array<Tile*, 8> _neighbors)
{
    // Populates / replaces the neighboring tile container.
    neighbors = _neighbors;
}
void Tile::revealNeighbors()
{
    // Based on State and mine content of the tile neighbors, set their state to REVEALED.
    int mines = 0;
    for (auto tiles : neighbors)
    {
        if (tiles != nullptr && tiles->isMine())
        {
            mines++;
        }
    }
    if (mines == 0)
    {
        for (auto item: neighbors)
        {
            if (item != nullptr)
            {
                if (item->getState() != REVEALED && item->getState() != FLAGGED && !item->isMine()) // reveals state of neighbors if they're not already revealed, not a mine, and don't neighbor mines
                {
                    item->setState(REVEALED);
                    int numMines = 0;
                    for (auto tiles : item->neighbors)
                    {
                        if (tiles != nullptr && tiles->isMine())
                        {
                            numMines++;
                        }
                    }
                    if (numMines == 0)
                    {
                        item->revealNeighbors();
                    }
                }
            }
        }
    }
    else
    {
        setState(REVEALED);
    }
}

void Tile::onClickLeft()
{
    // Defines the reveal behavior for a tile when the left mouse button is clicked inside its boundaries.
    if (getState() != FLAGGED)
    {
        setState(REVEALED);
        if (!isMine())
        {
            revealNeighbors();
        }
    }
}
void Tile::onClickRight()
{
    Toolbox& tools = Toolbox::getInstance();
    // Toggles this tile’s state between FLAGGED and HIDDEN.
    if(getState() == HIDDEN)
    {
        setState(FLAGGED);
    }
    else if (getState() == FLAGGED)
    {
        setState(HIDDEN);
    }
}
void Tile::draw()
{
    Toolbox& tools = Toolbox::getInstance();
    // Creates a sprite of this tile according to its state.
    if(getState() == HIDDEN)
    {
        sprite.setTexture(tools.hiddenTexture);
        sprite.setPosition(position);
        sprite2. setTexture(tools.hiddenTexture);
        sprite2.setPosition(sprite.getPosition());
    }
    else if (getState() == EXPLODED)
    {
        if(getDebugMode())
        {
            sprite.setTexture(tools.hiddenTexture); // if debug is active background is a hidden tile
        }
        else
        {
            sprite.setTexture(tools.revealedTexture); // otherwise background is a revealed tile
        }
        sprite2.setTexture(tools.mineTexture);
    }
    else if (getState() == FLAGGED)
    {
        sprite.setTexture(tools.hiddenTexture);
        sprite2.setTexture(tools.flagTexture);
    }
    else if (getState() == REVEALED)
    {
        sprite.setTexture(tools.revealedTexture);
        sprite2.setTexture(tools.revealedTexture);
        int mines = 0;
        for (auto tiles : neighbors)
        {
            if (tiles != nullptr && tiles->isMine())
            {
                mines++;
            }
        }
        int numBombs = mines;
        switch (numBombs)
        {
        case 0:
            sprite2.setTexture(tools.revealedTexture);
            break;
        case 1:
            sprite2.setTexture(tools.oneTexture);
            break;
        case 2:
            sprite2.setTexture(tools.twoTexture);
            break;
        case 3:
            sprite2.setTexture(tools.threeTexture);
            break;
        case 4:
            sprite2.setTexture(tools.fourTexture);
            break;
        case 5:
            sprite2.setTexture(tools.fiveTexture);
            break;
        case 6:
            sprite2.setTexture(tools.sixTexture);
            break;
        case 7:
            sprite2.setTexture(tools.sevenTexture);
            break;
        case 8:
            sprite2.setTexture(tools.eightTexture);
            break;
        default:
            throw std::runtime_error("More than 8 neighboring bombs counted");
        }
    }
}
