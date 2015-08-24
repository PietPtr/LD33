#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>

using namespace sf;

int main()
{
    srand(time(NULL));

    int windowWidth = 1280;
    int windowHeigth = 720;
    RenderWindow window(VideoMode(windowWidth, windowHeigth), "Float");
    window.setVerticalSyncEnabled(true);

    Game game(&window);

    game.initialize();

    while (window.isOpen())
    {
        game.update();
        game.draw();
    }

    return 0;
}

Vector2f normalize(Vector2f source)
{
    float length = sqrt(source.x * source.x + source.y * source.y);

    Vector2f normalizedVector;

    if (length != 0)
    {
        normalizedVector.x = source.x / length;
        normalizedVector.y = source.y / length;
    }
    else
    {
        normalizedVector.x = 0;
        normalizedVector.y = 0;
    }

    return normalizedVector;
}

Vector2f getDrawPosition(Vector2f worldPosition, Vector2f playerPosition)
{
    double X = worldPosition.x - playerPosition.x;
    double Y = worldPosition.y - playerPosition.y;

    return Vector2f(X, Y);
}

void drawString(RenderWindow* window, std::string text, Vector2f position, Texture* fontTexture, Color color, int newLine)
{
    bool shouldStartNewLine = false;

    int drawY = position.y;
    int drawX = position.x;

    int letterWidth = 5;
    int letterHeight = 7;

    int charactersSinceNewline = 0;
    for (int i = 0; i < text.length(); i++)
    {
        int num = (int)(text[i]);

        Sprite charSprite;
        charSprite.setTexture(*fontTexture);

        drawX += letterWidth + 1;

        if (num >= 48 && num <= 57)
            charSprite.setTextureRect(IntRect((num - 48) * letterWidth, 0, letterWidth, letterHeight));
        else if (num >= 65 && num <= 90)
            charSprite.setTextureRect(IntRect((num - 55) * letterWidth, 0, letterWidth, letterHeight));
        else if (num >= 97 && num <= 122)
            charSprite.setTextureRect(IntRect((num - 61) * letterWidth, 0, letterWidth, letterHeight));
        else if (num == 58)
            charSprite.setTextureRect(IntRect(62 * letterWidth, 0, letterWidth, letterHeight));
        else if (num == 46)
            charSprite.setTextureRect(IntRect(63 * letterWidth, 0, letterWidth, letterHeight));
        else if (num == 44)
            charSprite.setTextureRect(IntRect(64 * letterWidth, 0, letterWidth, letterHeight));
        else if (num == 32)
            charSprite.setTextureRect(IntRect(66 * letterWidth, 0, letterWidth, letterHeight));
        else if (num == 45)
            charSprite.setTextureRect(IntRect(67 * letterWidth, 0, letterWidth, letterHeight));
        else if (num == 39)
            charSprite.setTextureRect(IntRect(68 * letterWidth, 0, letterWidth, letterHeight));
        else if (num == 38)
        {
            shouldStartNewLine = true;
            charSprite.setTextureRect(IntRect(66 * letterWidth, 0, letterWidth, letterHeight));
        }
        else
            charSprite.setTextureRect(IntRect(65 * letterWidth, 0, letterWidth, letterHeight));

        charSprite.setColor(color);
        charSprite.setPosition(Vector2f(drawX, drawY));
        window->draw(charSprite);

        charactersSinceNewline++;

        if (newLine != -1 && charactersSinceNewline % newLine == 0 && i != 0)
        {
            shouldStartNewLine = true;
        }
        if (shouldStartNewLine && num == 32)
        {
            shouldStartNewLine = false;
            drawY += letterHeight + 4;
            drawX = position.x;
            charactersSinceNewline = 0;
        }
    }
}
