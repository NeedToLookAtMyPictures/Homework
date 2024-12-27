#include "Toolbox.h"
#include <cmath>

Toolbox* Toolbox::instance = nullptr;

Toolbox& Toolbox::getInstance()
{
    if(instance == nullptr)
    {
        instance = new Toolbox();
    }
    return *instance;
}

void Toolbox::pointDisplay(int points, sf::RenderTexture& renderTexture, Toolbox& tools)
{
    if (points < 0)
    {
        tools.scoreOne = negativeSign;
    }
    else
    {
        if (std::abs(points) / 100 == 0) { scoreOne = zeroDigit; }
        else if (std::abs(points) / 100 == 1) { scoreOne = oneDigit; }
        else if (std::abs(points) / 100 == 2) { scoreOne = twoDigit; }
        else if (std::abs(points) / 100 == 3) { scoreOne = threeDigit; }
        else if (std::abs(points) / 100 == 4) { scoreOne = fourDigit; }
        else if (std::abs(points) / 100 == 5) { scoreOne = fiveDigit; }
        else if (std::abs(points) / 100 == 6) { scoreOne = sixDigit; }
        else if (std::abs(points) / 100 == 7) { scoreOne = sevenDigit; }
        else if (std::abs(points) / 100 == 8) { scoreOne = eightDigit; }
        else if (std::abs(points) / 100 == 9) { scoreOne = nineDigit; }
    }

    if ((std::abs(points) / 10) % 10 == 0) { scoreTwo = zeroDigit; }
    else if ((std::abs(points) / 10) % 10 == 1) { scoreTwo = oneDigit; }
    else if ((std::abs(points) / 10) % 10 == 2) { scoreTwo = twoDigit; }
    else if ((std::abs(points) / 10) % 10 == 3) { scoreTwo = threeDigit; }
    else if ((std::abs(points) / 10) % 10 == 4) { scoreTwo = fourDigit; }
    else if ((std::abs(points) / 10) % 10 == 5) { scoreTwo = fiveDigit; }
    else if ((std::abs(points) / 10) % 10 == 6) { scoreTwo = sixDigit; }
    else if ((std::abs(points) / 10) % 10 == 7) { scoreTwo = sevenDigit; }
    else if ((std::abs(points) / 10) % 10 == 8) { scoreTwo = eightDigit; }
    else if ((std::abs(points) / 10) % 10 == 9) { scoreTwo = nineDigit; }

    if (std::abs(points) % 10 == 0) { scoreThree = zeroDigit; }
    else if (std::abs(points) % 10 == 1) { scoreThree = oneDigit; }
    else if (std::abs(points) % 10 == 2) { scoreThree = twoDigit; }
    else if (std::abs(points) % 10 == 3) { scoreThree = threeDigit; }
    else if (std::abs(points) % 10 == 4) { scoreThree = fourDigit; }
    else if (std::abs(points) % 10 == 5) { scoreThree = fiveDigit; }
    else if (std::abs(points) % 10 == 6) { scoreThree = sixDigit; }
    else if (std::abs(points) % 10 == 7) { scoreThree = sevenDigit; }
    else if (std::abs(points) % 10 == 8) { scoreThree = eightDigit; }
    else if (std::abs(points) % 10 == 9) { scoreThree = nineDigit; }

    // set positions of score sprites
    sf::Vector2f position(0, 32 * 16);
    scoreOne.setPosition(position);
    position = sf::Vector2f(23, 32 * 16);
    scoreTwo.setPosition(position);
    position = sf::Vector2f(46, 32 * 16);
    scoreThree.setPosition(position);
}

void Toolbox::mineSetter(int position)
{
    gameState->tiles.at(position)->setMine();
}

void Toolbox::tilePusher(sf::Vector2f position)
{
    gameState->tiles.push_back(std::make_shared<Tile>(position));
}

int Toolbox::tilesSize()
{
    return gameState->tiles.size();
}

bool Toolbox::isMine2D(int i, int j)
{
    return gameState->board[i][j] == 1;
}

int Toolbox::boardWidth()
{
    return gameState->board[0].size();
}

int Toolbox::boardHeight()
{
    return gameState->board.size();
}


void Toolbox::renderTexturing(sf::RenderTexture& renderTexture, Toolbox& tools, bool debug)
{
    int points = gameState->getMineCount() - gameState->getFlagCount();
    if(!debug)
    {
        renderTexture.clear();
        for(auto tile : tools.gameState->tiles)
        {
            tile->draw();
            renderTexture.draw(tile->sprite);
            renderTexture.draw(tile->sprite2);
        }
        renderTexture.draw(*tools.newGameButton->getSprite());
        renderTexture.draw(*tools.debugButton->getSprite());
        renderTexture.draw(*tools.testButton1->getSprite());
        renderTexture.draw(*tools.testButton2->getSprite());
        renderTexture.draw(*tools.testButton3->getSprite());
    }
    else
    {
        renderTexture.clear();
        for(auto tile : tools.gameState->tiles)
        {
            renderTexture.draw(tile->sprite);
            renderTexture.draw(tile->sprite2);
        }
        renderTexture.draw(*tools.newGameButton->getSprite());
        renderTexture.draw(*tools.debugButton->getSprite());
        renderTexture.draw(*tools.testButton1->getSprite());
        renderTexture.draw(*tools.testButton2->getSprite());
        renderTexture.draw(*tools.testButton3->getSprite());
    }
    pointDisplay(points, renderTexture, tools);
    renderTexture.draw(tools.scoreOne);
    renderTexture.draw(tools.scoreTwo);
    renderTexture.draw(tools.scoreThree);

}

void Toolbox::gameLoop(sf::Event event, Toolbox& tools, sf::RenderTexture& renderTexture)
{
    while (tools.window.pollEvent(event))
    {
        // check the type of the event...
        switch(event.type)
        {
            // window closed
        case sf::Event::Closed:
            tools.window.close();
            break;

            // key pressed
        case sf::Event::MouseButtonPressed:
            if(event.mouseButton.button == sf::Mouse::Right)
            {
                std::shared_ptr<Tile> eventTile;
                for (const auto& tile : tools.gameState->tiles)
                {
                    if (event.mouseButton.x < tile->getLocation().x + 32 && event.mouseButton.y < tile->getLocation().y + 32 && event.mouseButton.x > tile->getLocation().x && event.mouseButton.y > tile->getLocation().y)
                    {
                        if (tools.gameState->lost) { continue; }
                        tile->onClickRight();
                        if(getDebugMode())
                        {
                            if (!tile->isMine() && tile->getState() == Tile::FLAGGED)
                            {
                                tile->sprite2.setTexture(flagTexture);
                            }
                            else if(!tile->isMine() && tile->getState() == Tile::HIDDEN)
                            {
                                tile->sprite2.setTexture(hiddenTexture);
                            }
                        }
                        renderTexturing(renderTexture, tools, getDebugMode());
                    }
                }
            }
            else
            {
                std::shared_ptr<Tile> eventTile;
                for (const auto& tile : tools.gameState->tiles)
                {
                    if (event.mouseButton.x < tile->getLocation().x + 32 && event.mouseButton.y < tile->getLocation().y + 32 && event.mouseButton.x > tile->getLocation().x && event.mouseButton.y > tile->getLocation().y)
                    {
                        if (tools.gameState->lost) { continue; }
                        tile->onClickLeft();
                        if(getDebugMode())
                        {
                            toggleDebugMode();
                        }
                        renderTexturing(renderTexture, tools);
                    }
                }
                if (event.mouseButton.x < tools.newGameButton->getPosition().x + 64 && event.mouseButton.y < tools.newGameButton->getPosition().y + 64 && event.mouseButton.x > tools.newGameButton->getPosition().x && event.mouseButton.y > tools.newGameButton->getPosition().y)
                {
                    tools.newGameButton->onClick();
                    tools.gameState->setPlayStatus(GameState::PLAYING);
                    renderTexturing(renderTexture, tools);
                }
                else if (event.mouseButton.x < tools.debugButton->getPosition().x + 64 && event.mouseButton.y < tools.debugButton->getPosition().y + 64 && event.mouseButton.x > tools.debugButton->getPosition().x && event.mouseButton.y > tools.debugButton->getPosition().y)
                {
                    if (tools.gameState->lost) { continue; }
                    tools.debugButton->onClick();
                    renderTexturing(renderTexture, tools, getDebugMode());
                }
                else if (event.mouseButton.x < tools.testButton1->getPosition().x + 64 && event.mouseButton.y < tools.testButton1->getPosition().y + 64 && event.mouseButton.x > tools.testButton1->getPosition().x && event.mouseButton.y > tools.testButton1->getPosition().y)
                {
                    tools.testButton1->onClick();
                    renderTexturing(renderTexture, tools);
                }
                else if (event.mouseButton.x < tools.testButton2->getPosition().x + 64 && event.mouseButton.y < tools.testButton2->getPosition().y + 64 && event.mouseButton.x > tools.testButton2->getPosition().x && event.mouseButton.y > tools.testButton2->getPosition().y)
                {
                    tools.testButton2->onClick();
                    renderTexturing(renderTexture, tools);
                }
                else if (event.mouseButton.x < tools.testButton3->getPosition().x + 64 && event.mouseButton.y < tools.testButton3->getPosition().y + 64 && event.mouseButton.x > tools.testButton3->getPosition().x && event.mouseButton.y > tools.testButton3->getPosition().y)
                {
                    tools.testButton3->onClick();
                    renderTexturing(renderTexture, tools);
                }
            }
            break;
        }
    }

    bool won = true;
    for(const auto& item : tools.gameState->tiles)
    {
        if(!item->isMine() && (item->getState() == Tile::HIDDEN || item->getState() == Tile::FLAGGED)) // if any non-mine tiles are still hidden the player hasn't won
        {
            tools.gameState->setPlayStatus(GameState::PLAYING);
            won = false;
            break;
        }
    }
    if (won)
    {
        tools.gameState->setPlayStatus(GameState::WIN);
        renderTexturing(renderTexture, tools);
    }
}

void Toolbox::debugBehavior()
{
    if(getDebugMode())
    {
        for(auto item : gameState->tiles)
        {
            if(item->isMine())
            {
                item->sprite2.setTexture(mineTexture);
            }
        }
    }
    else
    {
        for(auto item : gameState->tiles)
        {
            item->draw();
        }
    }
}

void Toolbox::newGame()
{
    Toolbox& tools = getInstance();
    if(getDebugMode())
    {
        toggleDebugMode();
    }
    restart();
}

void Toolbox::debugGame()
{
    Toolbox& tools = getInstance();
    toggleDebugMode();
    tools.debugBehavior();
}

void Toolbox::testGameOne()
{
    if(getDebugMode())
    {
        toggleDebugMode();
    }
    Toolbox& tools = getInstance();
    // create tiles
    delete tools.gameState;
    tools.gameState = new GameState("./boards/testboard1.brd");
    for (int i = 0; i < tools.gameState->board.size(); i++) // rows
    {
        for (int j = 0; j < tools.gameState->board[0].size(); j++) // columns
        {
            sf::Vector2f pos = sf::Vector2f((32 * j), (32 * i));
            tools.gameState->tiles.push_back(std::make_shared<Tile>(pos));
            if (tools.gameState->board[i][j] == 1)
            {
                tools.gameState->tiles.at(tools.gameState->tiles.size() - 1)->setMine(); // sets tile to be a mine
            }
        }
    }
    // assign neighbors
    for (int i = 0; i < tools.gameState->board.size(); i++)
    {
        for (int j = 0; j < tools.gameState->board[0].size(); j++)
        {
            std::array<Tile*, 8>temp{};

            // top
            temp.at(0) = tools.gameState->getTile(j - 1, i - 1);
            temp.at(1) = tools.gameState->getTile(j - 1, i);
            temp.at(2) = tools.gameState->getTile(j - 1, i + 1);
            // center
            temp.at(3) = tools.gameState->getTile(j, i - 1);
            temp.at(4) = tools.gameState->getTile(j, i + 1);
            // bottom
            temp.at(5) = tools.gameState->getTile(j + 1, i - 1);
            temp.at(6) = tools.gameState->getTile(j + 1, i);
            temp.at(7) = tools.gameState->getTile(j + 1, i + 1);

            if(tools.gameState->getTile(j, i) != nullptr)
            {
                tools.gameState->getTile(j,i)->setNeighbors(temp);
            }
        }
    }
    tools.gameState->setPlayStatus(GameState::PLAYING);
}

void Toolbox::testGameTwo()
{
    if(getDebugMode())
    {
        toggleDebugMode();
    }
    Toolbox& tools = getInstance();
    // create tiles
    delete tools.gameState;
    tools.gameState = new GameState("./boards/testboard2.brd");
    for (int i = 0; i < tools.gameState->board.size(); i++) // rows
    {
        for (int j = 0; j < tools.gameState->board[0].size(); j++) // columns
        {
            sf::Vector2f pos = sf::Vector2f((32 * j), (32 * i));
            tools.gameState->tiles.push_back(std::make_shared<Tile>(pos));
            if (tools.gameState->board[i][j] == 1)
            {
                tools.gameState->tiles.at(tools.gameState->tiles.size() - 1)->setMine(); // sets tile to be a mine
            }
        }
    }
    // assign neighbors
    for (int i = 0; i < tools.gameState->board.size(); i++)
    {
        for (int j = 0; j < tools.gameState->board[0].size(); j++)
        {
            std::array<Tile*, 8>temp{};

            // top
            temp.at(0) = tools.gameState->getTile(j - 1, i - 1);
            temp.at(1) = tools.gameState->getTile(j - 1, i);
            temp.at(2) = tools.gameState->getTile(j - 1, i + 1);
            // center
            temp.at(3) = tools.gameState->getTile(j, i - 1);
            temp.at(4) = tools.gameState->getTile(j, i + 1);
            // bottom
            temp.at(5) = tools.gameState->getTile(j + 1, i - 1);
            temp.at(6) = tools.gameState->getTile(j + 1, i);
            temp.at(7) = tools.gameState->getTile(j + 1, i + 1);

            if(tools.gameState->getTile(j, i) != nullptr)
            {
                tools.gameState->getTile(j,i)->setNeighbors(temp);
            }
        }
    }
    tools.gameState->setPlayStatus(GameState::PLAYING);
}

void Toolbox::testGameThree()
{
    if(getDebugMode())
    {
        toggleDebugMode();
    }
    Toolbox& tools = getInstance();
    // create tiles
    delete tools.gameState;
    tools.gameState = new GameState("./boards/testboard3.brd");
    for (int i = 0; i < tools.gameState->board.size(); i++) // rows
    {
        for (int j = 0; j < tools.gameState->board[0].size(); j++) // columns
        {
            sf::Vector2f pos = sf::Vector2f((32 * j), (32 * i));
            tools.gameState->tiles.push_back(std::make_shared<Tile>(pos));
            if (tools.gameState->board[i][j] == 1)
            {
                tools.gameState->tiles.at(tools.gameState->tiles.size() - 1)->setMine(); // sets tile to be a mine
            }
        }
    }
    // assign neighbors
    for (int i = 0; i < tools.gameState->board.size(); i++)
    {
        for (int j = 0; j < tools.gameState->board[0].size(); j++)
        {
            std::array<Tile*, 8>temp{};

            // top
            temp.at(0) = tools.gameState->getTile(j - 1, i - 1);
            temp.at(1) = tools.gameState->getTile(j - 1, i);
            temp.at(2) = tools.gameState->getTile(j - 1, i + 1);
            // center
            temp.at(3) = tools.gameState->getTile(j, i - 1);
            temp.at(4) = tools.gameState->getTile(j, i + 1);
            // bottom
            temp.at(5) = tools.gameState->getTile(j + 1, i - 1);
            temp.at(6) = tools.gameState->getTile(j + 1, i);
            temp.at(7) = tools.gameState->getTile(j + 1, i + 1);

            if(tools.gameState->getTile(j, i) != nullptr)
            {
                tools.gameState->getTile(j,i)->setNeighbors(temp);
            }
        }
    }
    tools.gameState->setPlayStatus(GameState::PLAYING);
}