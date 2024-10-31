#include "ViewPort.h"
#include <iostream>

ViewPort::ViewPort(t_vector size) :
    PhysicsObject()
{
    // viewport does not cause physics collisions
    m_solid = false;

    // initialize the viewport size
    m_sizePx = size;

    // manually lock the camera
    m_playerPosition = {0LL, 0LL};

    // viewport positions the player center screen 
    m_viewportMode = VIEW_FOLLOW_PLAYER_CENTER;

    std::cout << "Viewport Position: " << m_position.x << ", " << m_position.y << std::endl;
}

bool ViewPort::init()
{
    return true;
}

void ViewPort::update(T_UINT64 dtime)
{
    if (m_viewportMode == VIEW_FOLLOW_PLAYER_CENTER)
    {
        // put the player in the center of the viewport
        setCenter(m_playerPosition);
    }
    else if (m_viewportMode == VIEW_FOLLOW_PLAYER_DYNAMIC)
    {
        // only move the camera if the player is close to the edge of the ViewPort
        t_vector offset_from_max = Vector2::subtract(m_playerPosition, maxPlayerPosition());
        t_vector offset_from_min = Vector2::subtract(m_playerPosition, minPlayerPosition());

        // player is too far right, adjust camera x+
        if (offset_from_max.x > 0LL)
            m_position.x += offset_from_max.x;
        // player is too far left, adjust camera x-
        else if (offset_from_min.x < 0LL)
            m_position.x += offset_from_min.x;
        
        // player is too far down, adjust camera y+
        if (offset_from_max.y > 0LL)
            m_position.y += offset_from_max.y;
        // player is too far up, adjust camera y-
        else if (offset_from_min.y < 0LL)
            m_position.y += offset_from_min.y;
    }
    else if (m_viewportMode == VIEW_LOCKED_IN_PLACE)
    {
        // do nothing, viewport position static
    }
    else
    {
        printf("WARN: unimplemented camera state\n");
    }
}

void ViewPort::setPlayerPosition(t_point playerPosition)
{
    m_playerPosition = playerPosition;
}

void ViewPort::setMode(t_viewport_mode mode)
{
    m_viewportMode = mode;
}

void ViewPort::vResolveCollision(PhysicsObject *obj)
{
    // do nothing
}

t_point ViewPort::maxPlayerPosition()
{
    return Vector2::add(
        m_position, 
        Vector2::scale(m_sizePx, 1.0 - 0.3)
    );
}

t_point ViewPort::minPlayerPosition()
{
    return Vector2::add(
        m_position, 
        Vector2::scale(m_sizePx, 0.3)
    );
}

void ViewPort::render()
{
    // do nothing
}

void ViewPort::destroy()
{
    delete this;
}
