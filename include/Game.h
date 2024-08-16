#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <iostream>

#include "Renderer.h"

class Game
{
    public:
        Game();
        bool init();
        void run();
        void cleanUp();

    private:
        Renderer * renderer;
        bool running;
        Uint32 lastFrameTime;
        void update();
        void render();
};

#endif // GAME_H