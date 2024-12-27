#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>
class Button{
public:
  Button(sf::Vector2f _position, const std::function<void(void)>& _onClick); // Constructs a new object at the specified _position which invokes the _onClick callback when clicked.
  sf::Vector2f getPosition(); // Returns the position of the button.
  sf::Sprite* getSprite(); // Returns the current sprite of the button.
  void setSprite(sf::Sprite* _sprite); // Sets this button’s visualization to the specified _sprite.
  void onClick() const; // Invokes the button’s callback method (usually called when clicked).
private:
  sf::Vector2f position;
  sf::Sprite sprite;
  std::function<void(void)> action;
};
#endif //BUTTON_H
