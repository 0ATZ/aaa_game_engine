#include "Rectangle.h"
#include <iostream>


Rectangle::Rectangle(GameWindow * window, int pixelWidth, int pixelHeight)
{
    m_position = {0,0};
    m_window = window;
    m_pixelWidth = pixelWidth;
    m_pixelHeight = pixelHeight;

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
        t_point point = m_position;
        m_window->renderSprite(
            m_defaultSprite, /* cached texture ID */
            point,  /* position of the top left corner */
            SCALE_QUADRA /* scale multiplier */
        );

        point.x = m_position.x + 80U;
        m_window->renderSprite(
            m_defaultSprite, /* cached texture ID */
            point,  /* position of the top left corner */
            SCALE_TRIPLE /* scale multiplier */
        );

        point.x = m_position.x + 144U;
        m_window->renderSprite(
            m_defaultSprite, /* cached texture ID */
            point,  /* position of the top left corner */
            SCALE_DOUBLE /* scale multiplier */
        );

        point.x = m_position.x + 192U;
        m_window->renderSprite(
            m_defaultSprite, /* cached texture ID */
            point,  /* position of the top left corner */
            SCALE_ORIGINAL /* scale multiplier */
        );
    }
}

void Rectangle::destroy()
{
    delete this;
}