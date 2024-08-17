#ifndef WINDOW_H
#define WINDOW_H

#include "SDL2/SDL.h"

class Renderer
{
    public:
        Renderer();
        bool init();
        void clear();
        void present();
        void destroy();
        bool isRunning();
        SDL_Renderer * getSDLRenderer();
        
    private:
        SDL_Window * window;
        SDL_Renderer * renderer;
};
#endif
