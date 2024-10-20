#include "Rectangle.h"
#include <iostream>


Rectangle::Rectangle(GameWindow * window, int pixelWidth, int pixelHeight)
{
    m_position = {0,0};
    m_window = window;
    m_sizePixels = {pixelWidth, pixelHeight};

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
            m_sizePixels /* render size pixel width x height */
        );
    }
}

void Rectangle::destroy()
{
    delete this;
}