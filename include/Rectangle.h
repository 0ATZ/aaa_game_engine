#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <SDL2/SDL.h>
#include "GameObject.h"

class Rectangle: public GameObject
{
    public:
        Rectangle(SDL_Renderer * sdlRenderer, int pixelWidth, int pixelHeight);
        bool init();
        void update();
        void render();
        void destroy();
        
    private:
        SDL_Renderer * m_sdlRenderer;
        int m_pixelWidth;
        int m_pixelHeight;
        int m_x_pos;
        int m_y_pos;
    
};
#endif
