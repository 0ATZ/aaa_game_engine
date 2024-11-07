#include "GameWindow.h"
#include "Rectangle.h"
#include "AnimatedSprite.h"
#include <iostream>

Rectangle::Rectangle(int pixelWidth, int pixelHeight)
{
    t_vector windowSize = GameWindow::get_window_size();
    m_position = {
        (windowSize.x/2) - (pixelWidth/2),
        (windowSize.y/2) - (pixelHeight/2)
    };
    m_sizePx = {pixelWidth, pixelHeight};
    m_weight = 11U;

    std::cout << "Player Position: " << m_position.x << ", " << m_position.y << std::endl;
    
    m_sprite = new AnimatedSprite("assets/sprites/numbers.bin", 36, 16, 16, 1.0);
    ((AnimatedSprite*)m_sprite)->start();

    // set default movement speed
    m_speedPx = 2UL;

}

bool Rectangle::init()
{
    return true;
}

void Rectangle::update(T_UINT64 dtime)
{
    T_UINT32 pKeys = GameWindow::get_player_keys();
    m_direction = { 0, 0 }; 
    if (pKeys & GameWindow::UP)
    {
        // std::cout << "up" << std::endl;
        --m_direction.y;
    }
    if (pKeys & GameWindow::DOWN)
    {
        // std::cout << "down" << std::endl;
        ++m_direction.y;
    }
    if (pKeys & GameWindow::LEFT)
    {
        // std::cout << "left" << std::endl;
        --m_direction.x;
    }
    if (pKeys & GameWindow::RIGHT)
    {
        // std::cout << "right" << std::endl;
        ++m_direction.x;
    }
    
    // std::cout << "direction x: " << direction.x << std::endl;
    // std::cout << "direction y: " << direction.y << std::endl;

    ((AnimatedSprite*)m_sprite)->update(dtime);
    PhysicsObject::update(dtime);

}

void Rectangle::render()
{
    GameWindow::render_sprite_viewport(m_sprite, m_position, m_sizePx);
}

void Rectangle::destroy()
{
    delete this;
}

void Rectangle::vResolveCollision(PhysicsObject *obj)
{
    PhysicsObject::resolveCollision(obj);
}

void Rectangle::vOnClick()
{
    printf("clicked the player!\n");
}
