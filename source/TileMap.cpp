#include "TileMap.h"
#include <cstring>
#include <GameWindow.h>

TileMap::TileMap(TileSet * tileSet, t_tilemap tileMap, T_UINT16 numRows, T_UINT16 numCols)
{
    m_position = {0,0};
    m_tileSet = tileSet;
    m_scale = SCALE_DOUBLE;
    
    // limit number of rows to MAX_TILEMAP_HEIGHT
    if (numRows > MAX_TILEMAP_HEIGHT)
    {
        m_numRows = MAX_TILEMAP_HEIGHT;
    }
    else
    {
        m_numRows = numRows;
    }
    
    // limit number of columns to MAX_TILEMAP_WIDTH
    if (numCols > MAX_TILEMAP_WIDTH)
    {
        m_numCols = MAX_TILEMAP_WIDTH;
    }
    else
    {
        m_numCols = numCols;
    }

    m_tileSizePx = Vector2::scale({TILE_WIDTH, TILE_HEIGHT}, m_scale); 

    // calculate the width and height of the entire map
    m_sizePx = Vector2::multiply({m_numRows, m_numCols}, m_tileSizePx);

    // calculate the total number of tiles in this map
    m_numTiles = m_numRows * m_numCols;

    // clear the member variable tilemap
    (void) memset(m_tileMap, 0, sizeof(t_tilemap));

    // copy the tilemap to a member variable
    (void) memcpy(m_tileMap, tileMap, sizeof(t_index) * m_numTiles);
}

void TileMap::render()
{
    // visit each row
    for (T_UINT16 row = 0U; row < m_numRows; row++)
    {
        // visit each column in each row
        for (T_UINT16 col = 0U; col < m_numCols; col++)
        {
            t_index L_tileID = getTileID(row, col);
            Tile * L_tile = m_tileSet->getTileFromID(L_tileID);
            if (L_tile) 
            {
                GameWindow::render_sprite_viewport(
                    L_tile, tilePosition(row, col), m_tileSizePx
                );    
            }
        }
    }
}

bool TileMap::init()
{
    return true;
}

void TileMap::update(T_UINT64 dtime)
{
    // do nothing
}

t_index TileMap::getTileID(T_UINT16 row, T_UINT16 col)
{
    // get an entry from the tilemap at (row, col)
    return m_tileMap[(row * m_numCols) + col];
}

t_point TileMap::tilePosition(T_UINT16 row, T_UINT16 col)
{
    // tile coordinates are calculated relative to the tilemap origin m_position
    // this way, the whole tilemap can be moved around the screen by updating m_position 
    t_point L_point = {
        // calculate x coordinate for the tile
        m_position.x + ((T_INT32)col * (T_INT32)TILE_WIDTH * m_scale),

        // calculate y coordinate for the tile 
        m_position.y + ((T_INT32)row * (T_INT32)TILE_HEIGHT * m_scale) 
    };
    return L_point;
}

void TileMap::destroy()
{
    delete this;
}
