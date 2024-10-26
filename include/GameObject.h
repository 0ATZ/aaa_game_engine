#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "GameTypes.h"
#include "Sprite.h"
#include "Vector2.h"

class GameObject
{

    public:
        GameObject() {
            m_position = { 0LL, 0LL };
            m_sizePx = { 0LL, 0LL };
            m_sprite = nullptr;
        };

        ~GameObject() { 
            delete m_sprite; 
        };

        virtual bool init()    = 0;
        virtual void update()  = 0;
        virtual void render()  = 0;
        virtual void destroy() = 0;
    
        void setPosition(t_point position)
        {
            m_position = position;
        }
        
        t_point getPosition()
        {
            return m_position;
        }

        t_vector getPositionAsVector()
        {
            return {m_position.x, m_position.y};
        }

        void movePosition(t_vector vector)
        {
            m_position = Vector2::add(
                m_position, 
                vector
            );
        }

        void setCenter(t_point position) {
            m_position = Vector2::subtract(
                position,
                Vector2::scale(m_sizePx, 0.5)
            );
        }

        t_point getCenter() {
            return Vector2::add(
                m_position,
                Vector2::scale(m_sizePx, 0.5)
            );
        }

        t_vector getSizePixels() 
        {
            return m_sizePx;
        }

        void setDefaultSprite(Sprite * sprite)
        {
            if (sprite != nullptr)
            {
                m_sprite = sprite;
            }
        }

    protected:
        t_point m_position;
        t_vector m_sizePx;
        Sprite * m_sprite;
};
#endif