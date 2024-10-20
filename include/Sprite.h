#ifndef SPRITE_H
#define SPRITE_H

#include "BaseTypes.h"
#include "GameTypes.h"

class Sprite
{
    public:
        Sprite(t_pixel *spritePixels, T_UINT16 width, T_UINT16 height);
        Sprite(t_tile *tilePixels);

        // void setSpritePixels(T_UINT16 *spritePixels, T_UINT16 width, T_UINT16 height, T_UINT16 textureID);
        T_UINT16 *getSpritePixels();
        T_UINT16 getNumPixels();

        void setTextureID(t_index textureID);
        t_index getTextureID();
        T_UINT16 getWidth();
        T_UINT16 getHeight();

    private:
        T_UINT16 * m_spritePixels;
        t_index m_textureID;
        T_UINT16 m_height;
        T_UINT16 m_width;
};
#endif