#include "PhysicsObject.h"
#include <iostream>
#include <cstdlib>

PhysicsObject::PhysicsObject()
{
    m_position = {0L, 0L};
    m_sizePx = {0L, 0L};
    m_direction = {0L, 0L};
    m_speedPx = 0UL;
    m_sprite = nullptr;
    m_solid = true;
    m_weight = 0U;
}

PhysicsObject::PhysicsObject(T_INT32 x, T_INT32 y, T_UINT16 widthPx, T_UINT16 heightPx, T_UINT16 weight)
{
    m_position = { x, y };
    m_sizePx = { widthPx, heightPx };
    m_direction = {0L, 0L};
    m_speedPx = 0UL;
    m_sprite = nullptr;
    m_solid = true;
    m_weight = weight;
    m_tempWeight = weight;
}

bool PhysicsObject::init()
{
    return true;
}

// TODO: implement acceleration, derived class can externally set the value 
void PhysicsObject::update(T_UINT64 dtime)
{
    if (m_weight < WEIGHT_STATIC)
    {
        // normalize the direction vector
        m_direction = Vector2::normalize(m_direction);
        
        // move the position
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
    // do nothing, derived class should handle render 
}

void PhysicsObject::destroy()
{
    delete this;
}

bool PhysicsObject::detectCollision(PhysicsObject *obj)
{
    bool collision = false;
    if ( obj != nullptr)
    {
        if (m_solid && obj->isSolid())
        {
            collision = GameObject::intersects(obj->getPosition(), obj->getSizePixels());
        }
    }
    return collision;
}

void PhysicsObject::resolveCollision(PhysicsObject * obj)
{
    if (obj != nullptr)
    {
        if (m_weight <= obj->getWeight())
        {
            // move this object if it is "lighter" than the other object
            GameObject::resolve(obj->getPosition(), obj->getSizePixels());
        }
        else
        {
            // move the other object if this one is "heavier"
            obj->resolve(m_position, m_sizePx);
        }
    }
}

void PhysicsObject::setTempWeight(T_UINT16 weight)
{
    m_tempWeight = weight;
}

T_UINT16 PhysicsObject::getTempWeight()
{
    return m_tempWeight;
}

void PhysicsObject::resetTempWeight()
{
    m_tempWeight = m_weight;
}

void PhysicsObject::setWeight(T_UINT16 weight)
{
    m_weight = weight;
}

T_UINT16 PhysicsObject::getWeight()
{
    return m_weight;
}

void PhysicsObject::setSpeed(T_UINT32 speedPx)
{
    m_speedPx = speedPx;
}

T_UINT32 PhysicsObject::getSpeed()
{
    return m_speedPx;
}

bool PhysicsObject::isSolid()
{
    return m_solid;
}