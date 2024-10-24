#include "Rectangle.h"
#include <iostream>

Rectangle::Rectangle(GameWindow * window, int pixelWidth, int pixelHeight)
{
    t_point windowSize = window->getSize();
    m_position = {
        (windowSize.x/2) - (pixelWidth/2),
        (windowSize.y/2) - (pixelHeight/2)
    };
    m_window = window;
    m_sizePx = {pixelWidth, pixelHeight};

    std::cout << "Player Position: " << m_position.x << ", " << m_position.y << std::endl;
    
    m_defaultSprite = new Tile("./assets/sprites/green_16x16.bin");
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