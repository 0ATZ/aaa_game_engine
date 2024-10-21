#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "GameTypes.h"

class GameObject
{
    public:
        virtual bool init()   = 0;
        virtual void update() = 0;
        virtual void render() = 0;
        virtual void destroy() = 0;
    
        void setPosition(t_point position)
        {
            m_position = position;
        }
        
        t_point getPosition()
        {
            return m_position;
        }

    protected:
        t_point m_position;
};
#endif