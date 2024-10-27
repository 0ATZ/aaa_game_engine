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
        virtual void update(T_UINT64 dtime)  = 0;
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

        void setSprite(Sprite * sprite)
        {
            if (sprite != nullptr)
            {
                m_sprite = sprite;
            }
        }
        
        Sprite * getSprite()
        {
            return m_sprite;
        }

        // position, width, and height define a 2D rectangular mesh, 
        // which represents the 2D space occupied by this object
        // the 2D rectangular mesh can be used to calculate collisions 
        // 
        // p is the upper left coordinate of the rectangle, 
        //      w is the width, and h is the height
        //
        //     (p.x, p.y) o--------------o (p.x + w, p.y)
        //                |              |
        //                |              |
        //                |              | h
        //                |              |
        //                |              |
        // (p.x, p.y + h) o--------------o (p.x + w, p.y + h) 
        //                       w
        bool intersects(t_point position, t_vector sizePx)
        {
            // Calculate 2 dimensional overlap
            T_INT32 dx = position.x - m_position.x;
            T_INT32 dy = position.y - m_position.y;

            // check if x values are close enough to collide
            if ((dx > 0) && (dx <= m_sizePx.x) ||      // this is to the left of obj, and x can collide
                (dx < 0) && (abs(dx) <= sizePx.x) ||  // obj is to the left of this, and x can collide
                (dx == 0))                             // x vals are the same
            
                // check if y values are close enough to collide
                if ((dy > 0) && (dy <= m_sizePx.y) ||     // this is above obj, and y can collide
                    (dy < 0) && (abs(dy) <= sizePx.x) || // obj is above this, and y can collide
                    (dy == 0))                            // y vals are the same
                    
                    // both x and y are close enough to collide
                    return true;

            // either the x position or y positions are too far
            return false;
        }

        bool intersects(GameObject * obj)
        {
            bool L_retVal = false;
            if (obj)
            {
                L_retVal = intersects(obj->getPosition(), obj->getSizePixels());
            }
            return L_retVal;
        }

    protected:
        t_point m_position;
        t_vector m_sizePx;
        Sprite * m_sprite;
};
#endif