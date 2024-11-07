#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include "GameTypes.h"
#include "Sprite.h"

class SpriteSheet
{
    public:
        SpriteSheet(const char * const filename, T_UINT16 numSprites, 
            T_UINT16 spriteWidthPx, T_UINT16 spriteHeightPx);
        ~SpriteSheet();

        Sprite * getSpriteByID(T_UINT16 spriteID);
        T_UINT16 getNumSprites();
        T_UINT16 getSpriteWidthPx();
        T_UINT16 getSpriteHeightPx();

    
    private:
        T_UINT16 m_numSprites;
        T_UINT16 m_spriteWidthPx;
        T_UINT16 m_spriteHeightPx;

        Sprite ** m_sprites;

};


#endif