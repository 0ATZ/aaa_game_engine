#include "Rectangle.h"
#include <iostream>

Rectangle::Rectangle(Window * window, int pixelWidth, int pixelHeight)
{
    m_x_pos = 0;
    m_y_pos = 0;
    m_window = window;
    m_pixelWidth = pixelWidth;
    m_pixelHeight = pixelHeight;
}

bool Rectangle::init()
{
    return true;
}

void Rectangle::update()
{
    const int speed = 2;
    if (m_window->getPlayerKeys() & Window::UP)
    {
        // std::cout << "up" << std::endl;
        m_y_pos = (m_y_pos - speed);
    }
    if (m_window->getPlayerKeys() & Window::DOWN)
    {
        // std::cout << "down" << std::endl;
        m_y_pos = (m_y_pos + speed);
    }
    if (m_window->getPlayerKeys() & Window::LEFT)
    {
        // std::cout << "left" << std::endl;
        m_x_pos = (m_x_pos - speed);
    }
    if (m_window->getPlayerKeys() & Window::RIGHT)
    {
        // std::cout << "right" << std::endl;
        m_x_pos = (m_x_pos + speed);
    }
}

void Rectangle::render()
{
    if (m_window != nullptr)
    {
        // Define the rectangle (x, y, width, height)
        SDL_Rect fillRect = { m_x_pos, m_y_pos, m_pixelWidth, m_pixelHeight };

        // Draw the filled rectangle
        SDL_RenderFillRect(m_window->getSDLRenderer(), &fillRect);

        // Optionally, draw the outline of the rectangle
        SDL_SetRenderDrawColor(m_window->getSDLRenderer(), 0x00, 0x00, 0x00, 0xFF); // Black outline
        SDL_RenderDrawRect(m_window->getSDLRenderer(), &fillRect);
    }
}

void Rectangle::destroy()
{
    delete this;
}