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
        int m_pixelHeight;  // TODO: how to calc collisions
        int m_pixelWidth;
        Sprite * m_defaultSprite;
};
#endif