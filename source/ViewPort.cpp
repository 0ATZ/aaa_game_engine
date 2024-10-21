#include "ViewPort.h"
#include <iostream>

ViewPort::ViewPort(PhysicsObject *player, T_UINT16 widthPixels, T_UINT16 heightPixels) :
    PhysicsObject()
{
    // store the player object
    m_player = player;

    // initialize the viewport size
    m_sizePx = {
        widthPixels, 
        heightPixels
    };

    // manually lock the camera
    m_followPlayer = true;

    // initialize the m_position
    this->centerToPlayer();

    std::cout << "Viewport Position: " << m_position.x << ", " << m_position.y << std::endl;
}

bool ViewPort::init()
{
    return true;
}

void ViewPort::update()
{
    // if camera is not locked, follow the player
    if (!this->isCameraLocked())
    {
        // TODO: make the camera follow player movement, not just jump to center
        this->centerToPlayer();
        // std::cout << "camera unlocked!" << std::endl;
    }
}

void ViewPort::centerToPlayer()
{
    // set the viewport position to the player position
    this->setCenter(
        m_player->getCenter()
    );
}

bool ViewPort::isCameraLocked()
{
    bool locked = true;

    if (m_followPlayer)
    {
        // manually unlocked the camera
        locked = false;
    }
    else 
    {
        // only move the camera if the player is close to the edge of the ViewPort
        t_point playerPosition = m_player->getPosition();
        t_point max = this->maxPlayerPosition();
        t_point min = this->minPlayerPosition();

        if (playerPosition.x >= max.x     // # right side, adjust camera x+
            || playerPosition.x <= min.x  // # left side, adjust camera x-
            || playerPosition.y >= max.y  // # bottom side, adjust camera y+ (screen down)
            || playerPosition.y <= min.y) // # top side, adjust camera y- (screen up)
        {
            // camera should follow the player around
            locked = false; 
        }
    }
    return locked;
}

t_point ViewPort::maxPlayerPosition()
{
    t_point L_point = {
        m_position.x + (T_INT32)(0.8 * m_sizePx.x),
        m_position.y + (T_INT32)(0.8 * m_sizePx.y)
    };
    return L_point;
}

t_point ViewPort::minPlayerPosition()
{
    t_point L_point = {
        m_position.x + (T_INT32)(0.2 * m_sizePx.x),
        m_position.y + (T_INT32)(0.2 * m_sizePx.y)
    };
    return L_point;
}

void ViewPort::render()
{
    // do nothing
}

void ViewPort::destroy()
{
    delete this;
}
