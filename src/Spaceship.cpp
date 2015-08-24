#include "Spaceship.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace sf;

const double G = 6.673e-11;
const double PI = 3.141592654;

Vector2f getDrawPosition(Vector2f worldPosition, Vector2f playerPosition);
Vector2f normalize(Vector2f source);

Spaceship::Spaceship(Vector2f _position, Vector2f _velocity)
{
    position = _position;
    velocity = _velocity;
}

void Spaceship::update(Time dt, Time totalTime, Vector2f planetPos)
{
    planetPos += Vector2f(64, 64);
    playerPosition = planetPos;

    double m1 = 100000; //spaceship mass
    double m2 = 2e8; //planet mass
    r = sqrt(std::pow(std::abs(planetPos.x - position.x), 2)+
                    std::pow(std::abs(planetPos.y - position.y), 2));

    double Fgrav = G * (m1 * m2 / pow(r, 2));

    if (dead == -1)
    {
        //double diagonal = r;
        gravitation.x = (Fgrav * (planetPos.x - position.x));
        gravitation.y = (Fgrav * (planetPos.y - position.y));

        velocity += gravitation;

        position.x += velocity.x * dt.asSeconds() * speed;
        position.y += velocity.y * dt.asSeconds() * speed;

        //std::cout << velocity.x << " " << velocity.y << " " << position.x << " " << position.y << " " <<  "\n";
        //std::cout << r << "\n";
    }

    if (r < 64 || r > 2048 || dead > -1)
    {
        if (dead == -1)
        {
            died = totalTime.asMilliseconds();
            if (deathCause == ALIVE)
            {
                if (r < 64)
                    deathCause = COLLISION;
                else if (r > 2048)
                    deathCause = DEEPSPACE;
            }
        }

        dead = totalTime.asMilliseconds();

    }
}

void Spaceship::draw(RenderWindow* window, int windowWidth, int windowHeight)
{
    Sprite spaceship;
    spaceship.setTexture(*spaceshipTextureptr);
    spaceship.setOrigin(Vector2f(16, 16));
    spaceship.setPosition(getDrawPosition(position, playerPosition));

    if (dead > -1)
    {
        spaceship.setColor(Color(255, 255, 255, 255 - (dead - died) / 10));
    }

    Vector2f up(0, -1);
    double dotProduct = up.x * velocity.x + up.y * velocity.y;
    double upLength = 1;
    double velocityLength = sqrt(pow(velocity.x, 2) + pow(velocity.y, 2));
    double angle = acos(dotProduct / (upLength * velocityLength)) * 180 / PI;

    if (position.x + velocity.x < position.x)
        angle = -angle;

    spaceship.setRotation(angle);

    window->draw(spaceship);

    int length = 48;
    int distance = 256;

    if (r > distance + length)
    {
        Vertex grav[] =
        {
            Vertex(Vector2f((distance) * -normalize(gravitation).x, (distance) * -normalize(gravitation).y)),
            Vertex(Vector2f((length + distance) * -normalize(gravitation).x, (length + distance) * -normalize(gravitation).y))
        };
        grav[0].color = Color(0, 200, 0, 255 - 255 * (r / 2048));
        grav[1].color = Color(0, 200, 0, 255 - 255 * (r / 2048));

        window->draw(grav, 2, Lines);
    }


    /*Vertex velo[] =
    {
        Vertex(Vector2f(getDrawPosition(position, playerPosition))),
        Vertex(Vector2f(getDrawPosition(position + Vector2f(velocity.x, velocity.y), playerPosition)))
    };
    velo[0].color = Color::Green;
    velo[1].color = Color::Green;

    window->draw(velo, 2, Lines);*/
}

