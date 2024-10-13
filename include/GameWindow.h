#ifndef WINDOW_H
#define WINDOW_H

#include "SDL2/SDL.h"
#include "GameObject.h"

class GameWindow : public GameObject
{
    public:
        GameWindow();
        bool init();
        void update();
        void render();
        void destroy();
        void clear();
        bool isRunning();
        SDL_Renderer * getSDLRenderer();
        uint16_t getPlayerKeys();
        
        static const uint16_t UP    = 0x01U; // 0001
        static const uint16_t DOWN  = 0x02U; // 0010
        static const uint16_t LEFT  = 0x04U; // 0100
        static const uint16_t RIGHT = 0x08U; // 1000
        
    private:
        SDL_Window * window;
        SDL_Renderer * renderer;
        bool m_running;
        uint16_t m_pKeys;
};
#endif
