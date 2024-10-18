#include "Sprite.h"

Sprite::Sprite(T_UINT16 *spritePixels, T_UINT16 height, T_UINT16 width, T_UINT16 textureID)
{
    m_spritePixels = spritePixels;
    m_height = height;
    m_width = width;
    m_textureID = textureID;
}

// need to update all relevant data
void Sprite::setSpritePixels(T_UINT16 *spritePixels, T_UINT16 width, T_UINT16 height, T_UINT16 textureID)
{
    m_spritePixels = spritePixels;
    m_height = height;
    m_width = width;
    m_textureID = textureID;
}

T_UINT16 * Sprite::getSpritePixels()
{
    return m_spritePixels;
}

T_UINT16 Sprite::getNumPixels()
{
    return (m_height * m_width);
}

T_UINT16 Sprite::getTextureID()
{
    return m_textureID;
}

T_UINT16 Sprite::getWidth()
{
    return m_width;
}

T_UINT16 Sprite::getHeight()
{
    return m_height;
}
