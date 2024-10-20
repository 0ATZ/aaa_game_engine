#include "Sprite.h"

Sprite::Sprite(t_pixel *spritePixels, T_UINT16 width, T_UINT16 height)
{
    m_spritePixels = spritePixels;
    m_height = height;
    m_width = width;
    m_textureID = 0x00U;
}

T_UINT16 * Sprite::getSpritePixels()
{
    return m_spritePixels;
}

T_UINT16 Sprite::getNumPixels()
{
    return (m_height * m_width);
}

void Sprite::setTextureID(t_index textureID)
{
    m_textureID = textureID;
}

t_index Sprite::getTextureID()
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
