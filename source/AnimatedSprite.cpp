#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(const char *const filename, T_UINT16 numSprites, 
    T_UINT16 spriteWidthPx, T_UINT16 spriteHeightPx, T_UINT16 frameDurationSec) : 
    Sprite(spriteWidthPx, spriteHeightPx)
{
    m_spriteSheet = new SpriteSheet(filename, numSprites, spriteWidthPx, spriteHeightPx);
    m_currentSprite = 0U;
    m_frameDurationSec = frameDurationSec;
    m_frameCounter = 0U;
    m_animate = false;
}

AnimatedSprite::~AnimatedSprite()
{
    delete m_spriteSheet;
}

void AnimatedSprite::update(T_UINT64 dtime)
{
    if (m_animate)
    {
        if (m_frameCounter >= m_frameDurationSec)
        {
            advanceFrame();
        }
        else
        {
            m_frameCounter += dtime;
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
    m_currentSprite = (m_currentSprite + 1) % m_spriteSheet->getNumSprites();
}

void AnimatedSprite::setCurrentFrame(T_UINT16 frameID)
{
    if (frameID < m_spriteSheet->getNumSprites())
    {
        m_currentSprite = frameID;
        m_frameCounter = 0U;
        Sprite * L_sprite = m_spriteSheet->getSpriteByID(frameID);
        m_texture = L_sprite->getTexture();
        m_width   = L_sprite->getWidth();
        m_height  = L_sprite->getHeight();
    }
}

T_UINT16 AnimatedSprite::getCurrentFrame()
{
    return m_currentSprite;
}
 