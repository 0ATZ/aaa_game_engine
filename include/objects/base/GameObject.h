#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "GameTypes.h"
#include "Sprite.h"
#include "Vector2.h"
#include <functional>

class GameObject
{

    public:
        GameObject() {
            m_position = { 0LL, 0LL };
            m_sizePx = { 0LL, 0LL };
            m_sprite = nullptr;
        };

        virtual ~GameObject() { 
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

        bool intersects(t_point position)
        {
            if (position.x >= m_position.x &&
                position.x < m_position.x + m_sizePx.x &&
                position.y >= m_position.y &&
                position.y < m_position.y + m_sizePx.y)
                return true;
            return false;
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
            // implement axis-aligned bounding box
            if (m_position.x > (position.x + sizePx.x) || // right
                (m_position.x + m_sizePx.x) < position.x || // left
                (m_position.y + m_sizePx.y) < position.y || // above
                m_position.y > (position.y + sizePx.y)) // below
            {
                return false;
            }
            return true;
        }


        bool isTouching(t_point position, t_vector size)
        {
            if ((m_position.x + m_sizePx.x == position.x) ||
                (m_position.x == position.x + size.x))
            {
                if ((m_position.y + m_sizePx.y) >= position.y &&
                    m_position.y <= (position.y + size.y))
                    return true;
            }
            
            if ((m_position.y + m_sizePx.y == position.y) ||
                (m_position.y == position.y + size.y)) 
            {
                if ((m_position.x + m_sizePx.x) >= position.x && 
                    m_position.x <= (position.x + size.x)) 
                    return true;
            }
            return false;    
        }

        // TODO: need to resolve one more pixel of overlap, or maybe intersects needs adjust?
        void resolve(t_point position, t_vector sizePx)
        {
            T_INT32 x_overlap = 0LL;
            T_INT32 y_overlap = 0LL;
            
            if (m_position.x <= position.x)
            {
                // this is to the left of obj
                x_overlap = (m_position.x + m_sizePx.x) - position.x;
            }
            else
            {
                // obj is to the left of this
                x_overlap = (position.x + sizePx.x) - m_position.x;
            }

            if (m_position.y <= position.y)
            {
                // this is above obj
                y_overlap = (m_position.y + m_sizePx.y) - position.y;
            }
            else
            {
                // obj is above this
                y_overlap = (position.y + sizePx.y) - m_position.y;
            }

            // move the position out of the intersection
            // whichever direction requires the least movement
            if (x_overlap > 0 && y_overlap > 0)
            {
                // x_overlap++;
                // y_overlap++;
                if (x_overlap <= y_overlap)
                {
                    // resolve in the x direction
                    if (m_position.x <= position.x)
                    {
                        m_position.x -= x_overlap;
                    }
                    else
                    {
                        m_position.x += x_overlap;
                    }
                }
                else
                {
                    // resolve in the y direction
                    if (m_position.y <= position.y)
                    {
                        m_position.y -= y_overlap;
                    }
                    else
                    {
                        m_position.y += y_overlap;
                    }
                }
            }
        }

        // derived classes should decide how to handle cursor clicks
        virtual void vOnClick() = 0;
        

    protected:
        t_point m_position;
        t_vector m_sizePx;
        Sprite * m_sprite;
};
#endif