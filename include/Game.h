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
        void update();
        void render();
        void cleanUp();
        bool registerObject(Rectangle * rectangle);
        bool isRunning();

    private:
        Renderer * renderer;
        bool running;
        Uint32 lastFrameTime;
        
        static const unsigned int MAX_OBJECTS = 64U;
        void * m_objects[MAX_OBJECTS];
        int m_objectCount;
};

#endif // GAME_H