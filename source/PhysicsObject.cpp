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
}

PhysicsObject::PhysicsObject(T_INT32 x, T_INT32 y, T_UINT16 widthPx, T_UINT16 heightPx)
{
    m_position = { x, y };
    m_sizePx = { widthPx, heightPx };
    m_direction = {0L, 0L};
    m_speedPx = 0UL;
    m_sprite = nullptr;
}

bool PhysicsObject::init()
{
    return true;
}

void PhysicsObject::update(T_UINT64 dtime)
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

void PhysicsObject::render()
{
    // TODO: render the sprite? 
}

void PhysicsObject::destroy()
{
    delete this;
}

void PhysicsObject::resolveCollision()
{

}
