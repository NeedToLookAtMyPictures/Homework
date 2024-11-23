#ifndef MEMER_H
#define MEMER_H

#include <SFML/Graphics.hpp>

sf::Image generateMeme(sf::Image base, sf::String topText, sf::String bottomText = "", int topX = 240, int topY = 160, int bottomX = 240, int bottomY = 320);

#endif //MEMER_H
