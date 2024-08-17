#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Rectangle.h"
#include "Renderer.h"

class Game
{
    public:
        Game();
        bool init();
        void update();
        void render();
        void destroy();
        bool registerObject(Rectangle * rectangle);
        bool isRunning();
        
    private:
        static const unsigned int MAX_OBJECTS = 64U;
        void * m_objects[MAX_OBJECTS];
        int m_objectCount;
        Renderer * renderer;
        Uint32 lastFrameTime;
        bool running;
};

#endif // GAME_H