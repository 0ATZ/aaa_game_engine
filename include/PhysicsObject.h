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

        void setCenterPosition(t_point position);
        void movePosition(t_point vector);
        t_point getCenterPosition();
        t_point getSizePixels();
        t_point invertPosition();

    protected:
        t_point m_sizePx;  // TODO: how to calc collisions
        t_point m_direction;
        T_UINT16 m_speedPx;
        Sprite * m_defaultSprite;
};

#endif

t_point getPosition();
