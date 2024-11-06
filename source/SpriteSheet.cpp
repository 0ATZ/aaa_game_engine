#include "SpriteSheet.h"
#include "BufferIO.h"
#include <iostream>

SpriteSheet::SpriteSheet(const char *const filename, T_UINT16 numSprites, 
    T_UINT16 spriteWidthPx, T_UINT16 spriteHeightPx)
{
    // store the sprite width and height 
    m_spriteWidthPx = spriteWidthPx;
    m_spriteHeightPx = spriteHeightPx;
    m_numSprites = numSprites;
    
    // allocate array of pointers for each sprite
    m_sprites = new Sprite*[numSprites];

    // allocate a temp buffer to read pixel data from the sprite sheet 
    const size_t PIXELS_PER_SPRITE = spriteWidthPx * spriteHeightPx;
    const size_t NUM_PIXELS = numSprites * PIXELS_PER_SPRITE;
    const size_t NUM_BYTES = NUM_PIXELS * sizeof(t_pixel); 
    t_pixel spriteSheetPixels[NUM_PIXELS] = {0};
    T_UINT16 bytes_read = BufferIO::readBuffer(
        filename, spriteSheetPixels, NUM_PIXELS * sizeof(t_pixel), 1
    );

    // check if read was successful
    if (bytes_read != NUM_BYTES)
    {
        printf("incorrect number of bytes read from spritesheet\n");
    }
    else
    {
        printf("spritesheet read %d bytes\n", bytes_read);
    }

    // process the pixel buffer into separate sprite objects
    for (T_UINT16 i = 0U; i < numSprites; i++)
    {
        // sprite object handles the texture creation
        t_pixel * spritePixels = &(spriteSheetPixels[PIXELS_PER_SPRITE*i]); 
        m_sprites[i] = new Sprite(spritePixels, spriteWidthPx, spriteHeightPx);
    }
}

SpriteSheet::~SpriteSheet()
{
    for (T_UINT16 i = 0U; i < m_numSprites; i++)
    {
        // deallocate each sprite object
        delete m_sprites[i];
    }
    // deallocate the array of pointers
    delete m_sprites;
}

Sprite *SpriteSheet::getSpriteByID(T_UINT16 spriteID)
{
    Sprite * L_sprite = nullptr;
    if (spriteID < m_numSprites)
    {
        L_sprite = m_sprites[spriteID];
    }
    else
    {
        printf("spritesheet index out of range: %d\n", spriteID);
    }
    return L_sprite;
}

T_UINT16 SpriteSheet::getNumSprites()
{
    return m_numSprites;
}

T_UINT16 SpriteSheet::getSpriteWidthPx()
{
    return m_spriteWidthPx;
}

T_UINT16 SpriteSheet::getSpriteHeightPx()
{
    return m_spriteHeightPx;
}
