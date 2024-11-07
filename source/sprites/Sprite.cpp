#include "Sprite.h"
#include "BufferIO.h"
#include "GameWindow.h"
#include <cstring>

Sprite::Sprite(T_UINT16 width, T_UINT16 height)
{
    // initialize variables
    m_spritePixels = nullptr;
    m_texture = nullptr;
    m_width = width;
    m_height = height;
}

Sprite::Sprite(const char * const filename, T_UINT16 width, T_UINT16 height)
{
    // allocate memory for the sprite
    m_spritePixels = new t_pixel[width * height];

    // read sprite pixel data from a binary file
    BufferIO::readRect_RGB565(filename, m_spritePixels, width, height);
    
    // initialize variables
    m_width = width;
    m_height = height;
    
    // create the texture which will be used for rendering
    GameWindow::create_texture(this);
}

Sprite::Sprite(t_pixel *spritePixels, T_UINT16 width, T_UINT16 height)
{
    // allocate memory for the sprite
    m_spritePixels = new t_pixel[width * height];
    
    // copy sprite pixels into the buffer
    memcpy(m_spritePixels, spritePixels, (width * height * sizeof(t_pixel)));
    
    // initialize variables
    m_width = width;
    m_height = height;
    GameWindow::create_texture(this);
}

Sprite::~Sprite()
{
    delete[] m_spritePixels;
}

t_pixel * Sprite::getSpritePixels()
{
    return m_spritePixels;
}

T_UINT16 Sprite::getNumPixels()
{
    return (m_height * m_width);
}

void Sprite::setTexture(void * texture)
{
    m_texture = texture;
}

void * Sprite::getTexture()
{
    return m_texture;
}

T_UINT16 Sprite::getWidth()
{
    return m_width;
}

T_UINT16 Sprite::getHeight()
{
    return m_height;
}
