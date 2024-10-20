#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "GameObject.h"
#include "GameWindow.h"
#include "TileSet.h"
#include "TileMap.h"

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
        TileSet * m_tileSet;
        TileMap * m_tileMap;
        bool running;
};

#endif // GAME_H