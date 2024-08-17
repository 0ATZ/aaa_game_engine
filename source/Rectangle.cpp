#include "Rectangle.h"

Rectangle::Rectangle(SDL_Renderer * sdlRenderer, int pixelWidth, int pixelHeight)
{
    m_x_pos = 0;
    m_y_pos = 0;
    
    m_pixelWidth = pixelWidth;
    m_pixelHeight = pixelHeight;
    
    if (m_sdlRenderer != nullptr)
    {
        m_sdlRenderer = sdlRenderer;
    }

}

bool Rectangle::init() 
{
    return true;
}

void Rectangle::update()
{
    m_x_pos = (m_x_pos + 1) % (800-100);
    m_y_pos = (m_y_pos + 1) % (600-100);
}

void Rectangle::render()
{
    if (m_sdlRenderer != nullptr)
    {
        // Define the rectangle
        SDL_Rect fillRect = { m_x_pos, m_y_pos, 100, 100 }; // x, y, width, height

        // Draw the filled rectangle
        SDL_RenderFillRect(m_sdlRenderer, &fillRect);

        // Optionally, draw the outline of the rectangle
        SDL_SetRenderDrawColor(m_sdlRenderer, 0x00, 0x00, 0x00, 0xFF); // Black outline
        SDL_RenderDrawRect(m_sdlRenderer, &fillRect);
    }
}

void Rectangle::destroy()
{
    delete this;
}