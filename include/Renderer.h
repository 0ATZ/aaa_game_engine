#ifndef WINDOW_H
#define WINDOW_H

#include "SDL2/SDL.h"
#include "GameObject.h"

class Renderer : public GameObject
{
    public:
        Renderer();
        bool init();
        void update();
        void render();
        void destroy();
        void clear();
        bool isRunning();
        SDL_Renderer * getSDLRenderer();
        
    private:
        SDL_Window * window;
        SDL_Renderer * renderer;
};
#endif
