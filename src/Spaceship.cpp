#include "Spaceship.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace sf;

const double G = 6.673e-11;
const double PI = 3.141592654;

Vector2f getDrawPosition(Vector2f worldPosition, Vector2f playerPosition);

Spaceship::Spaceship(Vector2f _position, Vector2f _velocity)
{
    position = _position;
    velocity = _velocity;
}

void Spaceship::update(Time dt, Vector2f planetPos)
{
    planetPos += Vector2f(64, 64);
    playerPosition = planetPos;

    double m1 = 100000; //spaceship mass
    double m2 = 1.9e10; //planet mass
    double r = sqrt(std::pow(std::abs(planetPos.x - position.x), 2)+
                    std::pow(std::abs(planetPos.y - position.y), 2));

    double Fgrav = G * (m1 * m2 / pow(r, 2));

    //double diagonal = r;
    gravitation.x = (Fgrav * (planetPos.x - position.x)) / r;
    gravitation.y = (Fgrav * (planetPos.y - position.y)) / r;

    velocity += gravitation;

    position.x += velocity.x * dt.asSeconds() * 5;
    position.y += velocity.y * dt.asSeconds() * 5;

    std::cout << velocity.x << " " << velocity.y << " " << position.x << " " << position.y << " " <<  "\n";
}

void Spaceship::draw(RenderWindow* window)
{
    Sprite spaceship;
    spaceship.setTexture(*spaceshipTextureptr);
    spaceship.setPosition(getDrawPosition(position, playerPosition));

    window->draw(spaceship);

    Vertex grav[] =
    {
        Vertex(Vector2f(Vector2f(-256, -256))),
        Vertex(Vector2f(Vector2f(-256, -256) + Vector2f(gravitation.x * 1000, gravitation.y * 1000)))
    };

    window->draw(grav, 2, Lines);

    Vertex velo[] =
    {
        Vertex(Vector2f(Vector2f(-256, -256))),
        Vertex(Vector2f(Vector2f(-256, -256) + Vector2f(velocity.x * 1000, velocity.y * 1000)))
    };
    velo[0].color = Color::Green;
    velo[1].color = Color::Green;

    window->draw(velo, 2, Lines);
}
