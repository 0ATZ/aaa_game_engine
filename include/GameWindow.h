#ifndef WINDOW_H
#define WINDOW_H

#include "BaseTypes.h"
#include "SDL2/SDL.h"
#include "Sprite.h"
#include "GameObject.h"

class GameWindow : public GameObject
{
    public:
        GameWindow(T_UINT16 width, T_UINT16 height);
        bool init();
        void update();
        void render();
        void destroy();
        void clear();
        bool isRunning();
        
        void * createTexture(t_pixel * pixels, T_UINT16 width, T_UINT16 height);
        void * createTexture(t_tile * tilePixels);
        void * createTexture(Sprite * sprite);
        t_vector getSize();

        void renderTexture(void *texture, t_point point, t_vector size);
        void renderSprite(Sprite *sprite, t_point point, t_vector size);

        SDL_Renderer * getSDLRenderer();
        T_UINT16 getPlayerKeys();

        static const T_UINT16 UP    = 0x01U; // 0001
        static const T_UINT16 DOWN  = 0x02U; // 0010
        static const T_UINT16 LEFT  = 0x04U; // 0100
        static const T_UINT16 RIGHT = 0x08U; // 1000
        
    private:

        // TODO: keep texture limit for memory constraints? 
        //   maybe want to just keep track of bytes consumed?
        // static const T_UINT16 MAX_TEXTURES = 32U;
        // t_index m_nextTexture;

        SDL_Window * window;
        SDL_Renderer * renderer;
        bool m_running;
        T_UINT16 m_pKeys;
};
#endif
