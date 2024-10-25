#include "Rectangle.h"
#include <iostream>

Rectangle::Rectangle(GameWindow * window, int pixelWidth, int pixelHeight)
{
    t_vector windowSize = window->getSize();
    m_position = {
        (windowSize.x/2) - (pixelWidth/2),
        (windowSize.y/2) - (pixelHeight/2)
    };
    m_window = window;
    m_sizePx = {pixelWidth, pixelHeight};

    std::cout << "Player Position: " << m_position.x << ", " << m_position.y << std::endl;
    
    m_sprite = new Tile("./assets/sprites/green_16x16.bin");
    (void) window->createTexture(m_sprite);
}

bool Rectangle::init()
{
    return true;
}

void Rectangle::update()
{
    const T_FLOAT32 movement_speed = 2.0;
    T_UINT16 pKeys = m_window->getPlayerKeys();
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

}

void Rectangle::render()
{
    if (m_window != nullptr)
    {
        m_window->renderSprite(
            m_sprite, /* cached texture ID */
            m_position,  /* position of the top left corner */
            m_sizePx /* render size pixel width x height */
        );
    }
}

void Rectangle::destroy()
{
    delete this;
}