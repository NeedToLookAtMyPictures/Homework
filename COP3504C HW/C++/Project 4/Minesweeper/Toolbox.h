#ifndef TOOLBOX_H
#define TOOLBOX_H
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "GameState.h"
#include <iostream>
#include "minesweeper.h"

class Toolbox{
public:
  ~Toolbox()
  {
    delete gameState;
    delete debugButton;
    delete newGameButton;
    delete testButton1;
    delete testButton2;
  }
  sf::RenderWindow window; // SFML application window
  GameState* gameState; // Primary game state representation
  Button* debugButton; // Reveals mines in debug mode
  Button* newGameButton; // Resets / starts new game
  Button* testButton1; // Loads test board #1
  Button* testButton2; // Loads test board #2
  Button* testButton3; // Loads test board #3
  sf::RenderTexture render;
  static Toolbox& getInstance(); // Returns a reference to the singular Toolbox instance.
  sf::Texture debugTexture;
  sf::Texture scoreTexture;
  sf::Texture faceTexture;
  sf::Texture loseTexture;
  sf::Texture winTexture;
  sf::Texture flagTexture;
  sf::Texture mineTexture;
  sf::Texture oneTexture;
  sf::Texture twoTexture;
  sf::Texture threeTexture;
  sf::Texture fourTexture;
  sf::Texture fiveTexture;
  sf::Texture sixTexture;
  sf::Texture sevenTexture;
  sf::Texture eightTexture;
  sf::Texture testOneTexture;
  sf::Texture testTwoTexture;
  sf::Texture testThreeTexture;
  sf::Texture hiddenTexture;
  sf::Texture revealedTexture;
  sf::Texture digits;
  sf::Sprite zeroDigit; // score digit symbols
  sf::Sprite oneDigit;
  sf::Sprite twoDigit;
  sf::Sprite threeDigit;
  sf::Sprite fourDigit;
  sf::Sprite fiveDigit;
  sf::Sprite sixDigit;
  sf::Sprite sevenDigit;
  sf::Sprite eightDigit;
  sf::Sprite nineDigit;
  sf::Sprite negativeSign;
  sf::Sprite scoreOne; // three score digits
  sf::Sprite scoreTwo;
  sf::Sprite scoreThree;
  void gameLoop(sf::Event event, Toolbox& tools, sf::RenderTexture& renderTexture);
  void renderTexturing(sf::RenderTexture& renderTexture, Toolbox& tools, bool debug = false);
  void debugBehavior();
  void mineSetter(int position);
  void tilePusher(sf::Vector2f position);
  int tilesSize();
  bool isMine2D(int i, int j);
  int boardWidth();
  int boardHeight();
  bool debug = false;
private:
  void pointDisplay(int points, sf::RenderTexture& renderTexture, Toolbox& tools);
  static Toolbox* instance;
  static void newGame();
  static void debugGame();
  static void testGameOne();
  static void testGameTwo();
  static void testGameThree();
  Toolbox()
  {
    // Default constructor; should be accessible only from within the class itself. This method initializes the buttons,
    // window, game board, and any other elements necessary to play the game.

    if (!render.create(800, 600))
    {
      throw std::runtime_error("Failed to create render");
    }

    // initialize sprites
    if(!debugTexture.loadFromFile("./images/debug.png"))
    {
      throw std::runtime_error("Failed to load debug texture from file");
    }
    if(!scoreTexture.loadFromFile("./images/digits.png"))
    {
      throw std::runtime_error("Failed to load score texture from file");
    }
    if(!faceTexture.loadFromFile("./images/face_happy.png"))
    {
      throw std::runtime_error("Failed to load face_happy texture from file");
    }
    if(!loseTexture.loadFromFile("./images/face_lose.png"))
    {
      throw std::runtime_error("Failed to load face_lose texture from file");
    }
    if(!winTexture.loadFromFile("./images/face_win.png"))
    {
      throw std::runtime_error("Failed to load face_win texture from file");
    }
    if(!flagTexture.loadFromFile("./images/flag.png"))
    {
      throw std::runtime_error("Failed to load flag texture from file");
    }
    if(!mineTexture.loadFromFile("./images/mine.png"))
    {
      throw std::runtime_error("Failed to load mine texture from file");
    }
    if(!oneTexture.loadFromFile("./images/number_1.png"))
    {
      throw std::runtime_error("Failed to load number_1 texture from file");
    }
    if(!twoTexture.loadFromFile("./images/number_2.png"))
    {
      throw std::runtime_error("Failed to load number_2 texture from file");
    }
    if(!threeTexture.loadFromFile("./images/number_3.png"))
    {
      throw std::runtime_error("Failed to load number_3 from file");
    }
    if(!fourTexture.loadFromFile("./images/number_4.png"))
    {
      throw std::runtime_error("Failed to load number_4 from file");
    }
    if(!fiveTexture.loadFromFile("./images/number_5.png"))
    {
      throw std::runtime_error("Failed to load number_5 from file");
    }
    if(!sixTexture.loadFromFile("./images/number_6.png"))
    {
      throw std::runtime_error("Failed to load number_6 from file");
    }
    if(!sevenTexture.loadFromFile("./images/number_7.png"))
    {
      throw std::runtime_error("Failed to load number_7 from file");
    }
    if(!eightTexture.loadFromFile("./images/number_8.png"))
    {
      throw std::runtime_error("Failed to load number_8 from file");
    }
    if(!testOneTexture.loadFromFile("./images/test_1.png"))
    {
      throw std::runtime_error("Failed to load test_1 texture from file");
    }
    if(!testTwoTexture.loadFromFile("./images/test_2.png"))
    {
      throw std::runtime_error("Failed to load test_2 texture from file");
    }
    if(!testThreeTexture.loadFromFile("./images/test_3.png"))
    {
      throw std::runtime_error("Failed to load test_3 texture from file");
    }
    if(!hiddenTexture.loadFromFile("./images/tile_hidden.png"))
    {
      throw std::runtime_error("Failed to load tile_hidden texture from file");
    }
    if(!revealedTexture.loadFromFile("./images/tile_revealed.png"))
    {
      throw std::runtime_error("Failed to load tile_revealed texture from file");
    }
    if(!digits.loadFromFile("./images/digits.png"))
    {
      throw std::runtime_error("Failed to load digits texture from file");
    }
    // create score sprites
    sf::IntRect bounds(0, 0, 23, 32);
    zeroDigit.setTexture(digits);
    zeroDigit.setTextureRect(bounds);
    bounds = sf::IntRect(22, 0, 23, 32);
    oneDigit.setTexture(digits);
    oneDigit.setTextureRect(bounds);
    bounds = sf::IntRect(43, 0, 23, 32);
    twoDigit.setTexture(digits);
    twoDigit.setTextureRect(bounds);
    bounds = sf::IntRect(64, 0, 23, 32);
    threeDigit.setTexture(digits);
    threeDigit.setTextureRect(bounds);
    bounds = sf::IntRect(85, 0, 23, 32);
    fourDigit.setTexture(digits);
    fourDigit.setTextureRect(bounds);
    bounds = sf::IntRect(106, 0, 23, 32);
    fiveDigit.setTexture(digits);
    fiveDigit.setTextureRect(bounds);
    bounds = sf::IntRect(127, 0, 23, 32);
    sixDigit.setTexture(digits);
    sixDigit.setTextureRect(bounds);
    bounds = sf::IntRect(148, 0, 23, 32);
    sevenDigit.setTexture(digits);
    sevenDigit.setTextureRect(bounds);
    bounds = sf::IntRect(169, 0, 23, 32);
    eightDigit.setTexture(digits);
    eightDigit.setTextureRect(bounds);
    bounds = sf::IntRect(190, 0, 23, 32);
    nineDigit.setTexture(digits);
    nineDigit.setTextureRect(bounds);
    bounds = sf::IntRect(207, 0, 23, 32);
    negativeSign.setTexture(digits);
    negativeSign.setTextureRect(bounds);

    // This method initializes the buttons
    sf::Vector2f position(368, 32 * 16);
    newGameButton = new Button(position, newGame);
    position = sf::Vector2f(368 + 2 * 64, 32 * 16);
    debugButton = new Button(position, debugGame);
    position = sf::Vector2f(368 + 3 * 64, 32 * 16);
    testButton1 = new Button(position, testGameOne);
    position = sf::Vector2f(368 + 4 * 64, 32 * 16);
    testButton2 = new Button(position, testGameTwo);
    position = sf::Vector2f(368 + 5 * 64, 32 * 16);
    testButton3 = new Button(position, testGameThree);

    sf::Sprite sprite;
    sprite.setTexture(faceTexture);
    newGameButton->setSprite(&sprite);
    sprite.setTexture(debugTexture);
    debugButton->setSprite(&sprite);
    sprite.setTexture(testOneTexture);
    testButton1->setSprite(&sprite);
    sprite.setTexture(testTwoTexture);
    testButton2->setSprite(&sprite);
    sprite.setTexture(testThreeTexture);
    testButton3->setSprite(&sprite);

    // game board,
    gameState = new GameState();
    // window,
    window.create(sf::VideoMode(800, 600), "P4 – Minesweeper, <Bayan Mahmoodi>");
    // and any other elements necessary to play the game.
  };
};
#endif //TOOLBOX_H
