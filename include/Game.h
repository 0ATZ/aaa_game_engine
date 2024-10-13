#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "GameObject.h"
#include "GameWindow.h"

class Game
{
    public:
        Game();
        bool init();
        void update();
        void render();
        void destroy();
        bool registerObject(GameObject * obj);
        bool isRunning();
        
    private:
        static const unsigned int MAX_OBJECTS = 64U;
        void * m_objects[MAX_OBJECTS];
        int m_objectCount;
        GameWindow * window;
        Uint32 lastFrameTime;
        bool running;
};

#endif // GAME_H