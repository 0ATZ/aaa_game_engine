#include "TileSet.h"
#include <iostream>

TileSet::TileSet(SDL_Renderer *renderer)
{
    m_tileCount = 0U;
    m_renderer = renderer;
    (void) memset(m_textureCache, 0, sizeof(t_texture_cache));
}

TileSet::TileSet(SDL_Renderer *renderer, t_tileset tileSet)
{
    for (m_tileCount = 0U; m_tileCount < TILESET_SIZE; m_tileCount++)
    {
        if (tileSet[m_tileCount])
        {
            // create SDL texture for each tile
            (void) this->addTile(tileSet[m_tileCount]);
        }
        else
        {
            break;
        }
    }
    std::cout << "Created tileset with " << m_tileCount << " tiles." << std::endl;
}

// returns true if there is an available space in the texture cache
bool TileSet::hasSpace()
{
    if (m_tileCount < TILESET_SIZE)
    {
        return true;
    }
    return false;
}

// returns the textureID 
t_index TileSet::addTile(t_tile *tile)
{
    t_index L_retVal = 0xFFU; // return the last texture ID if failed to add
    if (this->hasSpace())
    {
        SDL_Texture * L_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGB565, SDL_TEXTUREACCESS_STATIC, TILE_WIDTH, TILE_HEIGHT);

        if (!L_texture)
        {
            SDL_Log("Failed to create texture: %s", SDL_GetError());
        }
        else
        {
            // Update the texture with the pixel data
            SDL_UpdateTexture(L_texture, nullptr, tile, TILE_WIDTH * sizeof(t_pixel));
            m_textureCache[m_tileCount] = L_texture;
            L_retVal = m_tileCount;
            std::cout << "Tile created: " << m_tileCount << std::endl;
            m_tileCount++;
        }
    }
    else
    {
        std::cout << "ERROR: could not allocate texture." << std::endl;
    }

    return L_retVal;
}

SDL_Texture *TileSet::getTexture(t_index textureID)
{
    SDL_Texture* L_retVal = nullptr;
    if (textureID < m_tileCount)
    {
        L_retVal = m_textureCache[textureID];
    }
    return L_retVal;
}

void TileSet::renderTile(t_index textureID, t_point point, t_scale scale)
{
    if (textureID < m_tileCount)
    {
        SDL_Rect destRect = { point.x, point.y, TILE_WIDTH*scale, TILE_HEIGHT*scale };
        SDL_RenderCopy(m_renderer, m_textureCache[textureID], nullptr, &destRect);
    }
}
