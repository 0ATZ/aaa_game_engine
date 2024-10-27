#ifndef SPRITE_H
#define SPRITE_H

#include "BaseTypes.h"
#include "GameTypes.h"

class Sprite
{
    public:
        Sprite(const char *const filename, T_UINT16 width, T_UINT16 height);
        Sprite(t_pixel *spritePixels, T_UINT16 width, T_UINT16 height);
        ~Sprite();

        t_pixel *getSpritePixels();
        T_UINT16 getNumPixels();

        void setTexture(void * texture);
        void * getTexture();
        T_UINT16 getWidth();
        T_UINT16 getHeight();

    private:
        t_pixel * m_spritePixels;
        void * m_texture;  // for SDL implementation, this is SDL_Texture
        T_UINT16 m_height;
        T_UINT16 m_width;
};
#endif