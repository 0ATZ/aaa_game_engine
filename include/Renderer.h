#ifndef WINDOW_H
#define WINDOW_H

#include "SDL2/SDL.h"
#include "Rectangle.h"

class Renderer
{
    public:
        Renderer();
        bool init();
        void render();
        void destroy();
        bool isRunning();
        bool registerObject(Rectangle * rectangle);
        
    private:
        SDL_Window * window;
        SDL_Renderer * renderer;
        
        static const unsigned int MAX_OBJECTS = 64U;
        void * m_objects[MAX_OBJECTS];
        int m_objectCount;
};
#endif
