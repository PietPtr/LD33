#include "Planet.h"
#include <iostream>
#include "enums.h"

using namespace sf;

Vector2f normalize(Vector2f source);

Planet::Planet(Texture* _planetTextureptr)
{
    //planetTextureptr = _planetTextureptr;
}

void Planet::update(Time dt, bool focus)
{
    if (focus)
    {
        bool W = Keyboard::isKeyPressed(Keyboard::W);
        bool A = Keyboard::isKeyPressed(Keyboard::A);
        bool S = Keyboard::isKeyPressed(Keyboard::S);
        bool D = Keyboard::isKeyPressed(Keyboard::D);

        float velocityAcc = 2.0;

        if (W)
            velocity.y -= velocityAcc;
        if (A)
            velocity.x -= velocityAcc;
        if (S)
            velocity.y += velocityAcc;
        if (D)
            velocity.x += velocityAcc;
    }



    position.x += (double)(velocity.x * speed * dt.asSeconds());
    position.y += (double)(velocity.y * speed * dt.asSeconds());

    //std::cout << velocity.x << " " << velocity.y << " " << position.x << " " << position.y << " " <<  "\n";
}

void Planet::draw(RenderWindow* window)
{
    Sprite planet;
    planet.setTexture(*planetTextureptr);
    planet.setOrigin(64, 64);

    window->draw(planet);
}
