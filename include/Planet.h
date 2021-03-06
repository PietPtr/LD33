#ifndef PLANET_H
#define PLANET_H
#include <SFML/Graphics.hpp>

using namespace sf;

class Planet
{
    public:
        Planet(Texture* planetTextureptr);
        void setTexture(Texture* ptr1, Texture* ptr2) { planetTextureptr = ptr1; brokenPlanetTexture = ptr2; }
        Vector2<double> getPosition() { return position; }
        Vector2f getFloatPos() { return Vector2f(position.x, position.y); }
        void update(Time dt, bool focus);
        void draw(RenderWindow* window, bool gameover);
    protected:
    private:
        Vector2<double> position;
        Vector2f velocity;
        float speed = 5;

        Texture* planetTextureptr;
        Texture* brokenPlanetTexture;
};

#endif // PLANET_H
