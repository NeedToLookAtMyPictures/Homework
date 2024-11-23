#include "memer.h"
#include <iostream>

sf::Image generateMeme(sf::Image base, sf::String topText, sf::String bottomText, int topX, int topY, int bottomX, int bottomY){
//  1. Converting the Image into a Texture
    // Create a new texture
    sf::Texture memeTexture;

    // Read texture from given image
    if(!memeTexture.loadFromImage(base))
    {
        throw std::runtime_error("Failed to load texture");
    }

//  2. Wrapping the Texture in a Sprite
    // Create a new sprite
    sf::Sprite memeSprite;
    // Wrap the texture in the sprite
    memeSprite.setTexture(memeTexture);

//  3. Drawing the Sprite on a fresh & empty RenderTexture
    // Create a new render-window for visual output
    sf::RenderWindow window(sf::VideoMode(480, 480), "Meme Generator");
    // Create a new render-texture
    sf::RenderTexture render;
    if (!render.create(480, 480))
    {
        throw std::runtime_error("Failed to create render");
    }

//  4. Loading a Font, and using it to construct a Text element
    // create a new font
    sf::Font memeFont;
    // load font from our file
    if(!memeFont.loadFromFile("./Cave-Story.ttf"))
    {
        throw std::runtime_error("Failed to load font");
    }
    // initialize text using our font
    int fontSize = 30;
    sf::Text memeTextTop;
    memeTextTop.setFont(memeFont);
    memeTextTop.setCharacterSize(fontSize);
    memeTextTop.setStyle(sf::Text::Regular);
    sf::Text memeTextBottom = memeTextTop;

    memeTextTop.setString(topText);
    memeTextTop.setPosition(topX - memeTextTop.getLocalBounds().width / 2, topY);
    memeTextBottom.setString(bottomText);
    memeTextBottom.setPosition(bottomX - memeTextBottom.getLocalBounds().width / 2, bottomY);

    //  5. Drawing the Text on the RenderTexture
    render.draw(memeSprite);
    render.draw(memeTextTop);
    render.draw(memeTextBottom);

    //  6. Extracting an Image from a Texture, derived from the RenderTexture.
    sf::Texture memeTextureOutput(render.getTexture());
    sf::Image memeImage = memeTextureOutput.copyToImage();
    memeImage.flipVertically();
    if(!memeImage.saveToFile("./output/dog-meme.jpg"))
    {
        throw std::runtime_error("Failed to save image");
    }


//  7. Print my image
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        // We're done drawing to the render
        render.display();
        // Now we start rendering to the window, clear it first
        window.clear();
        // Draws the render-texture in the window
        sf::Sprite renderDrawn(render.getTexture());
        window.draw(renderDrawn);
        // End the current frame and display its contents on screen
        window.display();
    }
}

