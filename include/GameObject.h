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
        int m_xPos;
        int m_yPos;
        int m_pixelHeight;
        int m_pixelWidth;
        Sprite * m_defaultSprite;
};
#endif