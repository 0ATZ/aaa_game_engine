#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H


#include "GameTypes.h"
#include "Sprite.h"
#include "SpriteSheet.h"

class AnimatedSprite : public Sprite
{
    public:
        AnimatedSprite(const char * const filename, T_UINT16 numSprites,
            T_UINT16 spriteWidthPx, T_UINT16 spriteHeightPx, T_UINT16 frameDurationSec);
        ~AnimatedSprite();  // deallocate all sprites
    
        void update(T_UINT64 dtima);
        void start();
        void stop();

        void advanceFrame();
        void setCurrentFrame(T_UINT16 frameID);
        T_UINT16 getCurrentFrame();


    private:
        SpriteSheet * m_spriteSheet;
        T_UINT16 m_currentSprite;
        T_UINT64 m_frameDurationSec;
        T_UINT64 m_frameCounter;
        bool m_animate;

};


#endif