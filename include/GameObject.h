#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Sprite.h"

class GameObject
{
    public:
        virtual bool init()   = 0;
        virtual void update() = 0;
        virtual void render() = 0;
        virtual void destroy() = 0;
        
    protected:
        t_point m_position;
        t_point m_sizePixels;  // TODO: how to calc collisions
        Sprite * m_defaultSprite;
};
#endif