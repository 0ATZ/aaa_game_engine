#include "PhysicsObject.h"

PhysicsObject::PhysicsObject()
{
    m_position = {0L, 0L};
    m_sizePx = {0L, 0L};  // TODO: how to calc collisions
    m_direction = {0L, 0L};
    m_speedPx = 0U;
    m_defaultSprite = nullptr;
}

PhysicsObject::PhysicsObject(T_INT32 x, T_INT32 y, T_UINT16 widthPx, T_UINT16 heightPx)
{
    m_position = { x, y };
    m_sizePx = { widthPx, heightPx };
    m_direction = {0,0};
    m_speedPx = 0U;
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

void PhysicsObject::setCenterPosition(t_point position) {
    m_position.x = position.x - m_sizePx.x/2;
    m_position.y = position.y - m_sizePx.y/2;
}

t_point PhysicsObject::getCenterPosition() {
    t_point L_center = {
        m_position.x + m_sizePx.x/2,
        m_position.y + m_sizePx.y/2,
    };
    return L_center;
}

t_point PhysicsObject::getSizePixels() 
{
    return m_sizePx;
}

void PhysicsObject::movePosition(t_point vector) {
    m_position.x += vector.x;
    m_position.y += vector.y;
}

t_point PhysicsObject::invertPosition()
{
    t_point L_inverted = {
        m_position.x * -1,
        m_position.y * -1
    };
    return L_inverted;
}
