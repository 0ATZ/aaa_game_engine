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
        bool registerObject(Rectangle * rectangle);

    private:
        Renderer * renderer;
        bool running;
        Uint32 lastFrameTime;
        void update();
        void render();
        
        static const unsigned int MAX_OBJECTS = 64U;
        void * m_objects[MAX_OBJECTS];
        int m_objectCount;
};

#endif // GAME_H