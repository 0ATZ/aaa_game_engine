#include "AnimatedSprite.h"
#include <iostream>

AnimatedSprite::AnimatedSprite(const char *const filename, T_UINT16 numSprites, 
    T_UINT16 spriteWidthPx, T_UINT16 spriteHeightPx, T_FLOAT64 frameDurationSec) : 
    Sprite(spriteWidthPx, spriteHeightPx)
{
    m_spriteSheet = new SpriteSheet(filename, numSprites, spriteWidthPx, spriteHeightPx);
    
    m_currentFrameID = 0U;
    m_frameDurationSec = frameDurationSec;
    m_frameTimer = 0.0F;
    m_animate = false;

    setCurrentFrame(m_currentFrameID);
}

AnimatedSprite::~AnimatedSprite()
{
    delete m_spriteSheet;
}

void AnimatedSprite::update(T_UINT64 dtime)
{
    if (m_animate)
    {
        if (m_frameTimer >= m_frameDurationSec)
        {
            advanceFrame();
            m_frameTimer = 0.0F;
        }
        else
        {
            m_frameTimer += (dtime / 1000.0F);
        }
    }
}

void AnimatedSprite::start()
{
    m_animate = true;
}

void AnimatedSprite::stop()
{
    m_animate = false;
}

void AnimatedSprite::advanceFrame()
{
    m_currentFrameID = (m_currentFrameID + 1) % m_spriteSheet->getNumSprites();
    setCurrentFrame(m_currentFrameID);
}

void AnimatedSprite::setCurrentFrame(T_UINT16 frameID)
{
    if (frameID < m_spriteSheet->getNumSprites())
    {
        m_currentFrameID = frameID;
        m_frameTimer = 0.0F;
        Sprite * L_sprite = m_spriteSheet->getSpriteByID(frameID);
        m_texture = L_sprite->getTexture();
        m_width   = L_sprite->getWidth();
        m_height  = L_sprite->getHeight();
    }
}

T_UINT16 AnimatedSprite::getCurrentFrame()
{
    return m_currentFrameID;
}
 