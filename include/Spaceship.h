#ifndef SPACESHIP_H
#define SPACESHIP_H
#include <SFML/Graphics.hpp>

using namespace sf;

class Spaceship
{
    public:
        Spaceship(Vector2f position, Vector2f velocity);
        void update(Time dt, Time totalTime, Vector2f planetPos);
        void checkDead(Time totalTime);
        void draw(RenderWindow* window);

        void setTexture(Texture* ptr) { spaceshipTextureptr = ptr; }
        bool getFullyDead();
    protected:
    private:
        Vector2f position;
        Vector2f velocity;
        Vector2f gravitation;
        float speed = 5;

        Vector2f playerPosition;

        Texture* spaceshipTextureptr;

        int dead = -1;
        int died = -1;
};

#endif // SPACESHIP_H
