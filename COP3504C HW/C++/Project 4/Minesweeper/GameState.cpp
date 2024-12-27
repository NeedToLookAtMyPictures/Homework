#include "GameState.h"
#include "Toolbox.h"
#include <random>
#include <fstream>
#include <string>
#include <iostream>
GameState::GameState(sf::Vector2i _dimensions, int _numberOfMines)
{
    // Constructs a new random game state with specified tile _dimensions and the specified _numberOfMines.
    numberOfMines = _numberOfMines;
    std::vector<std::vector<int>>temp(_dimensions.y, std::vector<int>(_dimensions.x, 0));
    board = temp;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> rowDist(0, board.size() - 1);
    std::uniform_int_distribution<int> colDist(0, board[0].size() - 1);
    for (int i = 0; i < numberOfMines; i++)
    {
        int row = rowDist(gen);
        int col = colDist(gen);
        while(board[row][col] == 1)
        {
            // finds new random point if it's already a mine
            row = rowDist(gen);
            col = colDist(gen);
        }
        board[row][col] = 1; // make a random point a mine
    }
}
GameState::GameState(const char* filepath)
{
    // Constructs a game state based on the size, mine placement, and mine number specified at filepath.
    std::string temp;
    std::ifstream boardFile(filepath);
    if(!boardFile.is_open())
    {
        throw std::runtime_error("Board failed to open");
    }
    std::vector<std::vector<int>>tempVec(16, std::vector<int>(25, 0));
    board = tempVec;
    int row = 0;
    while(std::getline(boardFile, temp)) // store line of 01010101... in superTemp
    {
        for (int j = 0; j < temp.size(); j++)
        {
            board[row][j] = temp.at(j) - '0';
        }
        row++;
    }
    int numMines = 0;
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
        {
            if (board[i][j] == 1)
            {
                numMines++;
            }
        }
    }
    numberOfMines = numMines;
}

int GameState::getFlagCount()
{
    int flags = 0;
    for (auto tile : tiles)
    {
        if (tile->getState() == Tile::FLAGGED)
        {
            flags++;
        }
    }
    return flags;
}

Tile* GameState::getTile(int x, int y)
{
    // Returns a pointer to the Tile at the specified coordinates, or nullptr if out of bounds.
    try
    {
        if (x < 0 || y < 0 || x > board[0].size() - 1 || y > board.size() - 1)
        {
            return nullptr;
        }
        return tiles.at(y*board[0].size() + x).get();
    }
    catch (const std::out_of_range& oops)
    {
        return nullptr;
    }
}

void GameState::setPlayStatus(PlayStatus _status)
{
    Toolbox& tools = Toolbox::getInstance();
    // Sets the play status of the game.
    GameStatus = _status;
    if (_status == LOSS)
    {
        // reveal all mines and set "face_happy to face_lose"
        sf::Sprite sprite;
        sprite.setTexture(tools.loseTexture);
        tools.newGameButton->setSprite(&sprite);
        for(const auto& item : tiles)
        {
            if(item->isMine())
            {
                item->setState(Tile::REVEALED);
            }
        }
    }
    else if (_status == WIN)
    {
        // change face_happy to face_win
        sf::Sprite sprite;
        sprite.setTexture(tools.winTexture);
        tools.newGameButton->setSprite(&sprite);
    }
    else if (_status == PLAYING)
    {
        sf::Sprite sprite;
        sprite.setTexture(tools.faceTexture);
        tools.newGameButton->setSprite(&sprite);
    }
}