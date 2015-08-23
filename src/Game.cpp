#include <SFML/Graphics.hpp>
#include "Game.h"
#include "enums.h"

using namespace sf;

Game::Game(RenderWindow* _window)
{
    window = _window;
}

void Game::initialize()
{
    loadAudio(audioFileNames);
    loadTextures();
    player.setTexture(&planetTexture);
    testShip.setTexture(&spaceShipTexture);
}

void Game::update()
{
    Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
        if (event.type == Event::KeyPressed)
        {
            if (event.key.code == Keyboard::Escape)
            {
                window->close();
            }
        }
        if (event.type == Event::Resized)
        {
            windowWidth = event.size.width;
            windowHeight = event.size.height;
        }
        if (event.type == Event::LostFocus)
            focus = false;
        if (event.type == Event::GainedFocus)
            focus = true;
    }

    dt = clock.restart();
    totalTime += dt;

    player.update(dt, focus);
    testShip.update(dt, player.getFloatPos());

    if (Keyboard::isKeyPressed(Keyboard::F11))
    {
        Image Screen = window->capture();
        Screen.saveToFile("screenshot.png");
    }

    frame++;
}

void Game::draw()
{
    window->clear(Color(255, 255, 255));

    drawBackground();

    view.setSize(Vector2f(windowWidth, windowHeight));
    view.setCenter(viewPos);

    window->setView(view);

    /*Sprite test;
    test.setTexture(planetTexture);
    test.setOrigin(128, 128);
    test.setRotation(frame);
    test.setPosition(256, 256);
    window->draw(test);*/
    player.draw(window);
    testShip.draw(window);

    window->display();
}

void Game::drawBackground()
{
    Vector2f viewDistance;
    viewDistance.x = (windowWidth / 32 / 2) + 4;
    viewDistance.y = (windowHeight/ 32 / 2) + 4;

    Vector2<double> position = player.getPosition();

    int X = ((position.x - ((int)position.x % 32)) / 32) - (viewDistance.x);
    int Y = ((position.y - ((int)position.y % 32)) / 32) - (viewDistance.y);

    for (int y = Y; y < Y + viewDistance.y * 2; y++)
    {
        for (int x = X; x < X + viewDistance.x * 2; x++)
        {
            Vector2f tileDrawPos;
            tileDrawPos.x = x*32 - position.x;
            tileDrawPos.y = y*32 - position.y;

            Sprite star;
            star.setTexture(starTexture);
            star.setTextureRect(IntRect(32 * randint(0, 8, (x-32768) * (y+32768)), 0, 32, 32));
            star.setPosition(tileDrawPos);
            window->draw(star);
        }
    }
}

bool Game::isWindowOpen()
{
    return window->isOpen();
}

void Game::loadTextures()
{
    if (!planetTexture.loadFromFile("textures/planet.png"))
        window->close();
    if (!spaceShipTexture.loadFromFile("textures/spaceship.png"))
        window->close();
    if (!starTexture.loadFromFile("textures/stars.png"))
        window->close();
}

void Game::loadAudio(std::vector<std::string> audioFileNames)
{
    for (int i = 0; i < audioFileNames.size(); i++)
    {
        sfx.push_back(new Audio());
        sfx.back()->init(audioFileNames[i]);
    }
}

int Game::randint(int low, int high, int seed)
{
    srand(seed);
    int value = rand() % (high + 1 - low) + low;
    return value;
}

int Game::randint(int low, int high)
{
    int value = rand() % (high + 1 - low) + low;
    srand(totalTime.asMicroseconds() * value * rand());

    return value;
}