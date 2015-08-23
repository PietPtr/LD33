#ifndef SPACESHIP_H
#define SPACESHIP_H
#include <SFML/Graphics.hpp>

using namespace sf;

class Spaceship
{
    public:
        Spaceship(Vector2f position, Vector2f velocity);
        void update(Time dt, Vector2f planetPos);
        void draw(RenderWindow* window);

        void setTexture(Texture* ptr) { spaceshipTextureptr = ptr; }
    protected:
    private:
        Vector2f position;
        Vector2f velocity;
        Vector2f gravitation;
        float speed = 5;

        Vector2f playerPosition;

        Texture* spaceshipTextureptr;
};

#endif // SPACESHIP_H
