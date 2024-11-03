#include "TestBox.h"
#include "AnimatedSprite.h"
#include "GameWindow.h"
#include <iostream>

TestBox::TestBox(t_point position, T_UINT16 width, T_UINT16 height)
{
    m_sprite = new AnimatedSprite("./assets/sprites/red_green_blue.bin", 3, 16, 16, 1);
    ((AnimatedSprite*)m_sprite)->setCurrentFrame(1); // init to green square
    m_position = position;
    m_sizePx = {width, height};
    m_activated = false;
    m_weight = 10;
    m_solid = true;
    m_direction = {1, 0};
    m_speedPx = 1;
    m_timer = 0U;
}

TestBox::TestBox(t_point position, T_UINT16 width, T_UINT16 height, T_UINT16 weight) : 
    TestBox(position, width, height)
{
    m_weight = weight;
}


void TestBox::update(T_UINT64 dtime)
{
    // reset activation, collisions are checked after all objects update
    m_activated = false;
    
    m_timer += dtime;
    if (m_timer >= 4000)
    {
        // change direction every 2 seconds
        m_direction.x *= -1;
        m_timer = 0U;
    }
    

    // call base class to update position
    PhysicsObject::update(dtime);

}

void TestBox::render()
{
    if (m_activated)
    {
        // set to red square
        ((AnimatedSprite*)m_sprite)->setCurrentFrame(0);
    }
    else
    {
        // set to green square
        ((AnimatedSprite*)m_sprite)->setCurrentFrame(1);
    }
    
    // render the sprite
    GameWindow::render_sprite_viewport(m_sprite, m_position, m_sizePx);
}

void TestBox::vResolveCollision(PhysicsObject * obj)
{
    m_activated = true;
    PhysicsObject::resolveCollision(obj);
}

void TestBox::vOnClick()
{
    // printf("clicked a test box!\n");
    m_activated = true;
}
