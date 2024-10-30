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
    m_trackPosition = nullptr;

    std::cout << "Viewport Position: " << m_position.x << ", " << m_position.y << std::endl;
}

bool ViewPort::init()
{
    return true;
}

void ViewPort::update()
{
    // if camera is not locked, follow the player
    if (m_trackPosition != nullptr)
    {
        // TODO: make the camera follow player movement, not just jump to center
        this->setCenter(*m_trackPosition);
        // std::cout << "camera unlocked!" << std::endl;
    }
}

void ViewPort::trackPosition(t_point * position)
{
    m_trackPosition = position;
}

bool ViewPort::isTrackingPosition()
{
    bool tracking = false;

    if (m_trackPosition == nullptr)
    {
        tracking = true;
    }
    // else 
    // {
    //     // only move the camera if the player is close to the edge of the ViewPort
    //     // t_point playerPosition = m_player->getPosition();
    //     t_point max = this->maxPlayerPosition();
    //     t_point min = this->minPlayerPosition();

    //     if (playerPosition.x >= max.x     // # right side, adjust camera x+
    //         || playerPosition.x <= min.x  // # left side, adjust camera x-
    //         || playerPosition.y >= max.y  // # bottom side, adjust camera y+ (screen down)
    //         || playerPosition.y <= min.y) // # top side, adjust camera y- (screen up)
    //     {
    //         // camera should follow the player around
    //         locked = false; 
    //     }
    // }
    return tracking;
}

void ViewPort::vResolveCollision(PhysicsObject *obj)
{
    // do nothing
}

t_point ViewPort::maxPlayerPosition()
{
    return Vector2::add(
        m_position, 
        Vector2::scale(m_sizePx, 0.8)
    );
}

t_point ViewPort::minPlayerPosition()
{
    return Vector2::add(
        m_position, 
        Vector2::scale(m_sizePx, 0.2)
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
