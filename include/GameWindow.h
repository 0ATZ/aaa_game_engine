#ifndef WINDOW_H
#define WINDOW_H

#include "BaseTypes.h"
#include "SDL2/SDL.h"
#include "GameObject.h"
#include "TileSet.h"

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
        T_UINT16 createTexture(T_UINT16 * pixels, T_UINT16 width, T_UINT16 height);
        void renderSprite(T_UINT16 textureID, T_UINT16 x, T_UINT16 y, T_UINT16 width, T_UINT16 height);
        void renderScaledSprite(T_UINT16 textureID, T_UINT16 x, T_UINT16 y, T_UINT16 width, T_UINT16 height, T_UINT16 scale);
        SDL_Renderer * getSDLRenderer();
        T_UINT16 getPlayerKeys();

        static const T_UINT16 UP    = 0x01U; // 0001
        static const T_UINT16 DOWN  = 0x02U; // 0010
        static const T_UINT16 LEFT  = 0x04U; // 0100
        static const T_UINT16 RIGHT = 0x08U; // 1000
        
    private:

        static const T_UINT16 MAX_TEXTURES = 32U;
        SDL_Texture * m_textureCache[MAX_TEXTURES];
        T_UINT16 m_nextTexture;

        TileSet * m_tileSet;
        SDL_Window * window;
        SDL_Renderer * renderer;
        bool m_running;
        T_UINT16 m_pKeys;
};
#endif
