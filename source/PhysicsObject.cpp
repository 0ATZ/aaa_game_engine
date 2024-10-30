#include "PhysicsObject.h"
#include <iostream>
#include <cstdlib>

PhysicsObject::PhysicsObject()
{
    m_position = {0L, 0L};
    m_sizePx = {0L, 0L};  // TODO: how to calc collisions
    m_direction = {0L, 0L};
    m_speedPx = 0UL;
    m_sprite = nullptr;
    m_static = false;
    m_solid = true;
}

PhysicsObject::PhysicsObject(T_INT32 x, T_INT32 y, T_UINT16 widthPx, T_UINT16 heightPx)
{
    m_position = { x, y };
    m_sizePx = { widthPx, heightPx };
    m_direction = {0L, 0L};
    m_speedPx = 0UL;
    m_sprite = nullptr;
    m_static = false;
    m_solid = true;
}

bool PhysicsObject::init()
{
    return true;
}

// TODO: implement acceleration, derived class can externally set the value 
void PhysicsObject::update(T_UINT64 dtime)
{
    if (!m_static)
    {
        // normalize the direction vector
        m_direction = Vector2::normalize(m_direction);
        
        // TODO: calc collisions
        m_position = Vector2::add(
            m_position, 
            Vector2::scale(
                m_direction, 
                m_speedPx
            )
        );
    }
}

void PhysicsObject::render()
{
    // TODO: render the sprite? 
}

void PhysicsObject::destroy()
{
    delete this;
}

void PhysicsObject::resolveCollision(GameObject *obj)
{
    if (obj != nullptr)
    {
        // TODO: handle collision by moving non-static objects based on weight
        //    heavier objects move less than lighter ones
        //    how to handle movement when coliding? 
        //    maybe try implement static wall first
        if (!m_static)
        {
            t_point objPos = obj->getPosition();
            t_vector objSize = obj->getSizePixels();
            T_INT32 x_overlap = 0LL;
            T_INT32 y_overlap = 0LL;
            
            if (m_position.x <= objPos.x)
            {
                // this is to the left of obj
                x_overlap = (m_position.x + m_sizePx.x) - objPos.x;
            }
            else
            {
                // obj is to the left of this
                x_overlap = (objPos.x + objSize.x) - m_position.x;
            }

            if (m_position.y <= objPos.y)
            {
                // this is above obj
                y_overlap = (m_position.y + m_sizePx.y) - objPos.y;
            }
            else
            {
                // obj is above this
                y_overlap = (objPos.y + objSize.y) - m_position.y;
            }

            if (x_overlap > 0 && y_overlap > 0)
            {
                if (x_overlap <= y_overlap)
                {
                    // resolve in the x direction
                    if (m_position.x <= objPos.x)
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
                    if (m_position.y <= objPos.y)
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
    }
}

void PhysicsObject::setStatic(bool isStatic)
{
    m_static = isStatic;
}
