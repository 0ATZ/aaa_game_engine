#include "Rectangle.h"
#include <iostream>


Rectangle::Rectangle(GameWindow * window, int pixelWidth, int pixelHeight)
{
    m_xPos = 0;
    m_yPos = 0;
    m_window = window;
    m_pixelWidth = pixelWidth;
    m_pixelHeight = pixelHeight;

    // temp hard code a blue square
    t_tile blue_square;
    for (int i = 0; i < TILE_SIZE; i++)
    {
        blue_square[i] = 0x001FU;
    }
    
    T_UINT16 textureID = m_window->createTexture(blue_square, 16, 16);
    m_defaultSprite = new Sprite(blue_square, 16, 16, textureID);
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
        m_yPos = (m_yPos - speed);
    }
    if (pKeys & GameWindow::DOWN)
    {
        // std::cout << "down" << std::endl;
        m_yPos = (m_yPos + speed);
    }
    if (pKeys & GameWindow::LEFT)
    {
        // std::cout << "left" << std::endl;
        m_xPos = (m_xPos - speed);
    }
    if (pKeys & GameWindow::RIGHT)
    {
        // std::cout << "right" << std::endl;
        m_xPos = (m_xPos + speed);
    }
}

void Rectangle::render()
{
    if (m_window != nullptr)
    {
        m_window->renderScaledSprite(
            m_defaultSprite->getTextureID(), /* cached texture ID */
            m_xPos, m_yPos, /* position of the top left corner */
            m_defaultSprite->getWidth(),     /* width of the sprite */
            m_defaultSprite->getHeight(),     /* height of the sprite */
            4U
        );

        m_window->renderScaledSprite(
            m_defaultSprite->getTextureID(), /* cached texture ID */
            m_xPos + 80U, m_yPos, /* position of the top left corner */
            m_defaultSprite->getWidth(),     /* width of the sprite */
            m_defaultSprite->getHeight(),     /* height of the sprite */
            3U
        );

        m_window->renderScaledSprite(
            m_defaultSprite->getTextureID(), /* cached texture ID */
            m_xPos + 144U, m_yPos, /* position of the top left corner */
            m_defaultSprite->getWidth(),     /* width of the sprite */
            m_defaultSprite->getHeight(),     /* height of the sprite */
            2U
        );

        m_window->renderScaledSprite(
            m_defaultSprite->getTextureID(), /* cached texture ID */
            m_xPos + 192U, m_yPos, /* position of the top left corner */
            m_defaultSprite->getWidth(),     /* width of the sprite */
            m_defaultSprite->getHeight(),     /* height of the sprite */
            1U
        );
    }
}

void Rectangle::destroy()
{
    delete this;
}