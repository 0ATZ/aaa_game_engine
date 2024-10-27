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

    std::cout << "Player Position: " << m_position.x << ", " << m_position.y << std::endl;
    
    m_sprite = new AnimatedSprite("assets/sprites/spritesheet_4_16x16.bin", 4, 16, 16, 1.0);
    ((AnimatedSprite*)m_sprite)->start();
}

bool Rectangle::init()
{
    return true;
}

// TODO: call base class update for physics calcs 
void Rectangle::update(T_UINT64 dtime)
{
    const T_FLOAT32 movement_speed = 2.0;
    T_UINT16 pKeys = GameWindow::get_player_keys();
    t_vector movement = { 0, 0 }; 
    if (pKeys & GameWindow::UP)
    {
        // std::cout << "up" << std::endl;
        --movement.y;
    }
    if (pKeys & GameWindow::DOWN)
    {
        // std::cout << "down" << std::endl;
        ++movement.y;
    }
    if (pKeys & GameWindow::LEFT)
    {
        // std::cout << "left" << std::endl;
        --movement.x;
    }
    if (pKeys & GameWindow::RIGHT)
    {
        // std::cout << "right" << std::endl;
        ++movement.x;
    }

    // normalize and scale the vector,
    movement = Vector2::scale(
        Vector2::normalize(movement),
        movement_speed
    );
    
    // std::cout << "movement x: " << movement.x << std::endl;

    // transform the position 
    m_position = Vector2::add(
        m_position,
        movement
    );

    ((AnimatedSprite*)m_sprite)->update(dtime);

}

void Rectangle::render()
{
    GameWindow::render_sprite_viewport(m_sprite, m_position, m_sizePx);
}

void Rectangle::destroy()
{
    delete this;
}