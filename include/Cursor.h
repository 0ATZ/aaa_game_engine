#ifndef CURSOR_H
#define CURSOR_H

#include "GameTypes.h"
#include "PhysicsObject.h"

class Cursor : public PhysicsObject
{
    public:
        Cursor();
        
        void update(T_UINT64 dtime);
        void render();
        void destroy();
        void vResolveCollision(PhysicsObject * obj);

    private: 
        bool m_clicked;
        T_UINT64 m_timer;

};


#endif
