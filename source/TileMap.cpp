#include "TileMap.h"
#include <cstring>

// TODO: maybe support dynamically sized tilemaps?
//   can statically allocate a large buffer
//   then indicate the height and width in the constructor
TileMap::TileMap(TileSet * tileSet, t_tilemap tileMap)
{
    m_position = {0,0};
    m_tileSet = tileSet;
    m_scale = SCALE_DOUBLE;
    (void) memcpy(m_tileMap, tileMap, sizeof(t_tilemap));
}

void TileMap::render()
{
    // visit each row
    for (T_UINT16 row = 0U; row < TILEMAP_HEIGHT; row++)
    {
        // visit each column in each row
        for (T_UINT16 col = 0U; col < TILEMAP_WIDTH; col++)
        {
            // render tiles in a grid
            m_tileSet->renderTile(
                this->getTileID(row, col),   // get the tileID from the tilemap
                this->tilePosition(row, col), // get the (x, y) position for this tile
                m_scale   // scale factor for the rendered sprite
            );
        }
    }
}

t_index TileMap::getTileID(T_UINT16 row, T_UINT16 col)
{
    // get an entry from the tilemap at (row, col)
    return m_tileMap[(row * TILEMAP_WIDTH) + col];
}

t_point TileMap::tilePosition(T_UINT16 row, T_UINT16 col)
{
    // tile coordinates are calculated relative to the tilemap origin m_position
    // this way, the whole tilemap can be moved around the screen by updating m_position 
    t_point L_point = {
        // calculate x coordinate for the tile
        m_position.x + ((T_INT32)col * (T_INT32)TILEMAP_WIDTH * m_scale),

        // calculate y coordinate for the tile 
        m_position.y + ((T_INT32)row * (T_INT32)TILE_HEIGHT * m_scale) 
    };
    return L_point;
}

void TileMap::destroy()
{
    delete this;
}
