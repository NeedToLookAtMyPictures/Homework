#include "minesweeper.h"
#include "Toolbox.h"

int main()
{
  return launch();
}


void restart()
{
  // Resets all states/objects and generates a default game state (random board) and turns off debug mode if active.
  // The new state should be a default game state (25x16 with 50 randomly placed mines).
  Toolbox& tools = Toolbox::getInstance();
  tools.gameState = new GameState();
  for (int i = 0; i < tools.boardHeight(); i++) // rows
  {
    for (int j = 0; j < tools.boardWidth(); j++) // columns
    {
      sf::Vector2f pos = sf::Vector2f((32 * j), (32 * i));
      tools.tilePusher(pos);
      if (tools.isMine2D(i,j))
      {
        tools.mineSetter(tools.tilesSize() - 1); // sets tile to be a mine
      }
    }
  }
  // assign neighbors
  for (int i = 0; i < tools.boardHeight(); i++)
  {
    for (int j = 0; j < tools.boardWidth(); j++)
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

void render()
{
  Toolbox& tools = Toolbox::getInstance();

  // render iterates down GameState.board drawing each sprite accordingly
  // sprites are being deleted
  tools.renderTexturing(tools.render, tools);

  // Draws the all UI elements according to the current gameState and debug mode.
  while (tools.window.isOpen())
  {
    // Event processing
    sf::Event event;
    tools.gameLoop(event, tools, tools.render);
    // We're done drawing to the render
    tools.render.display();
    // Now we start rendering to the window, clear it first
    tools.window.clear();
    // Draws the render-texture in the window
    sf::Sprite renderDrawn(tools.render.getTexture());
    tools.window.draw(renderDrawn);
    // End the current frame and display its contents on screen
    tools.window.display();
  }
}

bool getDebugMode()
{
  Toolbox& tools = Toolbox::getInstance();
  // Returns the true if debug mode is active, and false otherwise.
  return tools.debug;
}

void toggleDebugMode()
{
  Toolbox& tools = Toolbox::getInstance();
  // Flips the debug mode on/off. (Debug mode should initially be off/false.)
  if (getDebugMode())
  {
    tools.debug = false;
  }
  else
  {
    tools.debug = true;
  }
}