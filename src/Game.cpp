#include <SFML/Graphics.hpp>
#include "Game.h"
#include "enums.h"

using namespace sf;

void drawString(RenderWindow* window, std::string text, Vector2f position, Texture* fontTexture, Color color, int newLine);

Game::Game(RenderWindow* _window)
{
    window = _window;
}

void Game::initialize()
{
    loadAudio(audioFileNames);
    loadTextures();
    player.setTexture(&planetTexture, &brokenPlanetTexture);
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

    if (!gameover)
        player.update(dt, focus);
    else
        player.update(dt, false);


    if (spaceships.size() < 1 && frame % 1 == 0)
    {
        Vector2f newShipPos;
        switch(randint(0, 3))
        {
        case(0):
            newShipPos = Vector2f(player.getFloatPos().x - windowWidth / 2.0 + randint(-0, 256),
                                  player.getFloatPos().y - windowHeight / 2.0 + randint(-0, 256));
            break;
        case(1):
            newShipPos = Vector2f(player.getFloatPos().x - windowWidth / 2.0 + randint(-0, 256),
                                  player.getFloatPos().y + windowHeight / 2.0 + randint(-0, 256));
            break;
        case(2):
            newShipPos = Vector2f(player.getFloatPos().x + windowWidth / 2.0 + randint(-0, 256),
                                  player.getFloatPos().y + windowHeight / 2.0 + randint(-0, 256));
            break;
        case(3):
            newShipPos = Vector2f(player.getFloatPos().x + windowWidth / 2.0 + randint(-0, 256),
                                  player.getFloatPos().y - windowHeight / 2.0 + randint(-0, 256));
            break;
        }
        //std::cout << newShipPos.x << " " << newShipPos.y << " " << spaceships.size() << "\n";
        spaceships.push_back(Spaceship(newShipPos, Vector2f(0, 0)));
        spaceships.at(spaceships.size() - 1).setTexture(&spaceShipTexture, &pointerTexture);
    }

    for (int i = spaceships.size() - 1; i >= 0; i--)
    {
        if (spaceships.at(i).getFullyDead() != ALIVE)
        {

            if (spaceships.at(i).getFullyDead() == 1)
                health -= 20;
            else if (spaceships.at(i).getFullyDead() == 2)
                points += 1;

            spaceships.erase(spaceships.begin() + i);
        }
    }

    if (health <= 0)
    {
        gameover = true;
        health = 0;
    }

    for (int i = 0; i < spaceships.size(); i++)
    {
        spaceships[i].update(dt, totalTime, player.getFloatPos());
    }

    if (Keyboard::isKeyPressed(Keyboard::F11))
    {
        Image Screen = window->capture();
        Screen.saveToFile("screenshot.png");
    }

    //std::cout << "Points: " << points << ", Health: " << health << "\n";

    frame++;
}

void Game::draw()
{
    window->clear(Color(255, 255, 255));

    drawBackground();

    view.setSize(Vector2f(windowWidth, windowHeight));
    view.setCenter(viewPos);

    window->setView(view);

    player.draw(window, gameover);

    for (int i = 0; i < spaceships.size(); i++)
    {
        spaceships[i].draw(window, windowWidth, windowHeight);
    }

    drawString(window, "SHIPS FLUNG INTO DEEP SPACE: " + std::to_string(points), Vector2f(-windowWidth / 2.0, -windowHeight / 2.0 + 3), &fontTexture, Color(0, 200, 0), 100);
    drawString(window, "PLANET HEALTH: " + std::to_string(health), Vector2f(-windowWidth / 2.0, -windowHeight / 2.0 + 13), &fontTexture, Color(0, 200, 0), 100);

    if (gameover)
    {
        for (int i = 0; i < 16; i++)
        {
            drawString(window, "GAMEOVER", Vector2f(-24, 72 + i * 9), &fontTexture, Color(0, 200, 0), 100);
        }
    }

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
    if (!brokenPlanetTexture.loadFromFile("textures/brokenplanet.png"))
        window->close();
    if (!fontTexture.loadFromFile("textures/font.png"))
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
