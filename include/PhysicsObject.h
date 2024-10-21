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
        void update();
        void render();
        void destroy();
    
    // TODO: perform physics calculations to move position
    // TODO: calculate collisions
    protected:
        t_vector m_velocityPx;
};

#endif

t_point getPosition();
