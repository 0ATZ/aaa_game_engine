#include "Rectangle.h"

Rectangle::Rectangle(int pixelWidth, int pixelHeight)
{
    m_x_pos = 0;
    m_y_pos = 0;
    m_pixelWidth = pixelWidth;
    m_pixelHeight = pixelHeight;
}

void Rectangle::update()
{
    m_x_pos = (m_x_pos + 1) % (800-100);
    m_y_pos = (m_y_pos + 1) % (600-100);
}

void Rectangle::render(SDL_Renderer * sdlRenderer)
{
    if (sdlRenderer != nullptr)
    {
        // Define the rectangle
        SDL_Rect fillRect = { m_x_pos, m_y_pos, 100, 100 }; // x, y, width, height

        // Draw the filled rectangle
        SDL_RenderFillRect(sdlRenderer, &fillRect);

        // Optionally, draw the outline of the rectangle
        SDL_SetRenderDrawColor(sdlRenderer, 0x00, 0x00, 0x00, 0xFF); // Black outline
        SDL_RenderDrawRect(sdlRenderer, &fillRect);
    }
}