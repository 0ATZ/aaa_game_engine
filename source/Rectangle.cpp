#include "Rectangle.h"
#include <iostream>


// TODO: make this Rectangle constructor better. For now, init with zero
//   I think need a sprite manager and only keep track of a void ptr here
//   that way, do not need game window, only x,y position
Rectangle::Rectangle(GameWindow * window, int pixelWidth, int pixelHeight) :
    PhysicsObject(0,0,0,0) 
{
    t_point windowSize = window->getSize();
    m_position = {
        (windowSize.x/2) - (pixelWidth/2),
        (windowSize.y/2) - (pixelHeight/2)
    };
    m_window = window;
    m_sizePx = {pixelWidth, pixelHeight};

    std::cout << "Player Position: " << m_position.x << ", " << m_position.y << std::endl;

    // hard code a 16x16 blue square
    t_tile blue_square;
    for (int i = 0; i < TILE_SIZE; i++)
    {
        blue_square[i] = 0x001FU;
    }
    
    m_defaultSprite = new Tile(&blue_square);
    (void) window->createTexture(m_defaultSprite);
}

bool Rectangle::init()
{
    return true;
}

void Rectangle::update()
{
    const int speed = 2;
    uint16_t pKeys = m_window->getPlayerKeys();
    if (pKeys & GameWindow::UP)
    {
        // std::cout << "up" << std::endl;
        m_position.y = (m_position.y - speed);
    }
    if (pKeys & GameWindow::DOWN)
    {
        // std::cout << "down" << std::endl;
        m_position.y = (m_position.y + speed);
    }
    if (pKeys & GameWindow::LEFT)
    {
        // std::cout << "left" << std::endl;
        m_position.x = (m_position.x - speed);
    }
    if (pKeys & GameWindow::RIGHT)
    {
        // std::cout << "right" << std::endl;
        m_position.x = (m_position.x + speed);
    }
}

void Rectangle::render()
{
    if (m_window != nullptr)
    {
        m_window->renderSprite(
            m_defaultSprite, /* cached texture ID */
            m_position,  /* position of the top left corner */
            m_sizePx /* render size pixel width x height */
        );
    }
}

void Rectangle::destroy()
{
    delete this;
}