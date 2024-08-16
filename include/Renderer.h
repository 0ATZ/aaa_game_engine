#ifndef WINDOW_H
#define WINDOW_H

#include "SDL2/SDL.h"

class Renderer
{
    public:
        Renderer();
        bool init();
        void render();
        void destroy();
        bool isRunning();
        
    private:
        SDL_Window * window;
        SDL_Renderer * renderer;
        int xpos, ypos;
        void renderRectangle(int x, int y);

};
#endif
