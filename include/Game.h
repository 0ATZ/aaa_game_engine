#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "GameObject.h"
#include "PhysicsObject.h"
#include "TileSet.h"
#include "TileMap.h"
#include "PhysicsEngine.h"

class Game
{
    public:
        Game();
        bool init();
        void update(T_UINT64 dtime);
        void render();
        void destroy();
        bool registerObject(GameObject * obj);
        bool isRunning();
        
    private:
        static const T_UINT16 MAX_OBJECTS = 64U;
        GameObject * m_objects[MAX_OBJECTS];
        GameObject * m_player;
        GameObject * m_cursor;
        T_UINT16 m_objectCount;
        TileSet * m_tileSet;
        PhysicsEngine * m_physicsEngine;
        bool running;

        // temp var for debug
        Sprite * m_redSquare;
        Sprite * m_greenSquare;
        GameObject * m_testSquare;
        bool m_intersect;

};

#endif // GAME_H