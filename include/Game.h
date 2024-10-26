#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "GameObject.h"
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
        GameObject * m_objects[MAX_OBJECTS];
        GameObject * m_player;
        int m_objectCount;
        TileSet * m_tileSet;
        TileMap * m_tileMap;
        bool running;

        // temp var for debug
        Sprite * m_redSquare;
        Sprite * m_greenSquare;
        GameObject * m_testSquare;
        bool m_intersect;
};

#endif // GAME_H