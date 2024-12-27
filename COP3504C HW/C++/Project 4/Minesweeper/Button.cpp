#include "Button.h"

Button::Button(sf::Vector2f _position, const std::function<void(void)>& _onClick)
{
    // Constructs a new object at the specified _position which invokes the _onClick callback when clicked.
    position = _position;
    action = _onClick;
}

sf::Vector2f Button::getPosition()
{
    // Returns the position of the button.
    return position;
}

sf::Sprite* Button::getSprite()
{
    // Returns the current sprite of the button.
    return &sprite;
}
void Button::setSprite(sf::Sprite* _sprite)
{
    // Sets this button’s visualization to the specified _sprite.
    sprite = *_sprite;
    sprite.setPosition(position);
}
void Button::onClick() const
{
    // Invokes the button’s callback method (usually called when clicked).
    // Explode, Reveal, etc
    action();
}
