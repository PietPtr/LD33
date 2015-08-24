#ifndef SPACESHIP_H
#define SPACESHIP_H
#include <SFML/Graphics.hpp>
#include "enums.h"

using namespace sf;

class Spaceship
{
    public:
        Spaceship(Vector2f position, Vector2f velocity);
        void update(Time dt, Time totalTime, Vector2f planetPos);
        void checkDead(Time totalTime);
        void draw(RenderWindow* window, int windowWidth, int windowHeight);

        void setTexture(Texture* ptr1, Texture* ptr2) { spaceshipTextureptr = ptr1; pointerTextureptr = ptr2; }
        DeathCause getFullyDead() { return deathCause; };
    protected:
    private:
        Vector2f position;
        Vector2f velocity;
        Vector2f gravitation;
        float speed = 5;
        double r;

        Vector2f playerPosition;

        Texture* spaceshipTextureptr;
        Texture* pointerTextureptr;

        int dead = -1;
        int died = -1;
        DeathCause deathCause = ALIVE;
};

#endif // SPACESHIP_H
