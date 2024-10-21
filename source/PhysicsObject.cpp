#include "PhysicsObject.h"

PhysicsObject::PhysicsObject()
{
    m_position = {0L, 0L};
    m_sizePx = {0L, 0L};  // TODO: how to calc collisions
    m_velocityPx = {0L, 0L};
    m_defaultSprite = nullptr;
}

PhysicsObject::PhysicsObject(T_INT32 x, T_INT32 y, T_UINT16 widthPx, T_UINT16 heightPx)
{
    m_position = { x, y };
    m_sizePx = { widthPx, heightPx };
    m_velocityPx = {0L, 0L};
    m_defaultSprite = nullptr;
}

bool PhysicsObject::init()
{
    return true;
}

void PhysicsObject::update()
{
    // TODO: calc movement using speed and stuff
}

void PhysicsObject::render()
{
    // TODO: render the sprite? 
}

void PhysicsObject::destroy()
{
    delete this;
}
