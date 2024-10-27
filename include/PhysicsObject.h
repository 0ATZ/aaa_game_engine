#ifndef PHYSICSOBJECT_H 
#define PHYSICSOBJECT_H 

#include "GameTypes.h"
#include "GameObject.h"
#include "Sprite.h"

class PhysicsObject : public GameObject
{
    public:
        PhysicsObject();
        PhysicsObject(T_INT32 x, T_INT32 y, T_UINT16 widthPx, T_UINT16 heightPx);

        bool init();
        void update(T_UINT64 dtime);
        void render();
        void destroy();

        void resolveCollision();
    
    // TODO: perform physics calculations to move position
    // TODO: calculate collisions
    protected:
        T_UINT32 m_speedPx; // pixels per frame
        t_vector m_direction;
        
};

#endif

