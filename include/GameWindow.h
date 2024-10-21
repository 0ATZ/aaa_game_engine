#ifndef WINDOW_H
#define WINDOW_H

#include "BaseTypes.h"
#include "SDL2/SDL.h"
#include "Sprite.h"

class GameWindow
{
    public:
        GameWindow(T_UINT16 width, T_UINT16 height);
        bool init();
        void update();
        void render();
        void destroy();
        void clear();
        bool isRunning();
        
        t_index createTexture(t_pixel * pixels, T_UINT16 width, T_UINT16 height);
        t_index createTexture(t_tile * tilePixels);
        t_index createTexture(Sprite * sprite);
        t_point getSize();

        void renderTexture(t_index textureID, t_point point, T_UINT16 width, T_UINT16 height, t_scale scale);
        void renderSprite(Sprite * sprite, t_point point, t_scale scale);
        void renderSprite(Sprite *sprite, t_point point, t_point size);

        bool textureExists(t_index textureID);

        SDL_Renderer * getSDLRenderer();
        T_UINT16 getPlayerKeys();

        static const T_UINT16 UP    = 0x01U; // 0001
        static const T_UINT16 DOWN  = 0x02U; // 0010
        static const T_UINT16 LEFT  = 0x04U; // 0100
        static const T_UINT16 RIGHT = 0x08U; // 1000
        
    private:

        static const T_UINT16 MAX_TEXTURES = 32U;
        SDL_Texture * m_textureCache[MAX_TEXTURES];
        t_index m_nextTexture;

        SDL_Window * window;
        SDL_Renderer * renderer;
        bool m_running;
        T_UINT16 m_pKeys;
        T_UINT16 m_windowWidth;
        T_UINT16 m_windowHeight;

};
#endif
