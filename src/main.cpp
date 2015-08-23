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
