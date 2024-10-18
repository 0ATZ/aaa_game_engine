#ifndef SPRITE_H
#define SPRITE_H

#include "BaseTypes.h"

// TODO: create SDL texture here, then pass to the game window to render sprite
// TODO: decouple from SDL lib somehow?
class Sprite
{
    public:
        Sprite(T_UINT16 *spritePixels, T_UINT16 height, T_UINT16 width, T_UINT16 textureID);
        void setSpritePixels(T_UINT16 *spritePixels, T_UINT16 width, T_UINT16 height, T_UINT16 textureID);
        T_UINT16 *getSpritePixels();
        T_UINT16 getNumPixels();

        T_UINT16 getTextureID();
        T_UINT16 getWidth();
        T_UINT16 getHeight();

    private:
        T_UINT16 * m_spritePixels;
        T_UINT16 m_height;
        T_UINT16 m_width;
        T_UINT16 m_textureID;
};
#endif