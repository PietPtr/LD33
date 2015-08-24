#include <SFML/Graphics.hpp>
#include <iostream>
#include "Audio.h"
#include "Planet.h"
#include "Spaceship.h"

using namespace sf;

class Game
{
    public:
        Game(RenderWindow* window);
        void initialize();
        void update();
        void draw();
        void drawBackground();
        bool isWindowOpen();

        void loadAudio(std::vector<std::string> fileNames);
        void loadTextures();;

        int randint(int low, int high, int seed);
        int randint(int low, int high);
    protected:
    private:
        RenderWindow* window;
        View view;

        int windowWidth = 1280;
        int windowHeight = 720;

        bool focus = true;

        Time dt;
        Time totalTime;
        Clock clock;
        int frame = 0;

        Texture planetTexture;
        Texture spaceShipTexture;
        Texture starTexture;
        Texture pointerTexture;

        std::vector<std::string> audioFileNames;

        Planet player { &planetTexture };
        int health = 100;
        int points = 0;

        Vector2f viewPos { 0, 0 };

        std::vector<Audio*> sfx;

        std::vector<Spaceship> spaceships;
};
