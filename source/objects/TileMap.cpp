#include "TileMap.h"
#include <cstring>
#include <GameWindow.h>
#include <BufferIO.h>
#include <stdio.h>

TileMap::TileMap(const char * const filename, TileSet * tileSet, T_UINT16 numRows, T_UINT16 numCols)
{
    m_position = {0,0};
    m_tileSet = tileSet;
    
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
    
    // calculate the tile size after the scale / zoom 
    m_scaledTileSize = Vector2::scale(m_tileSet->getTileSize(), (T_FLOAT32)SCALE_DOUBLE);
    
    // calculate the width and height of the entire map
    m_sizePx = Vector2::multiply({m_numRows, m_numCols}, m_scaledTileSize);
    
    // calculate the total number of tiles in this map
    m_numTiles = m_numRows * m_numCols;

    // allocate a new buffer for the tilemap
    m_tileMap = new T_UINT8[m_numTiles];
    if (m_tileMap == nullptr)
    {
        printf("failed to allocate tilemap buffer of length: %d\n", m_numTiles);
    }

    // read the tilemap bytes from the file into the new buffer
    T_UINT16 bytes_read = BufferIO::readBuffer(
        filename, m_tileMap, m_numTiles, 1
    );

    // check if read was successful
    if (bytes_read != (sizeof(t_index) * m_numTiles))
    {
        printf("incorrect number of bytes read from tilemap\n");
    }
    else
    {
        printf("tilemap read %d bytes\n", bytes_read);
    }
}

TileMap::~TileMap()
{
    delete[] m_tileMap;
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
            Sprite * L_tile = m_tileSet->getSpriteByID(L_tileID);
            if (L_tile) 
            {
                GameWindow::render_sprite_viewport(
                    L_tile, tilePosition(row, col), m_scaledTileSize
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

void TileMap::setTileID(T_UINT16 row, T_UINT16 col, t_index tileID)
{
    // set an entry from the tilemap at (row, col)
    m_tileMap[(row * m_numCols) + col] = tileID;
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
    return Vector2::add(
        m_position,
        Vector2::multiply({col, row}, m_scaledTileSize)
    );
}

void TileMap::destroy()
{
    delete this;
}

void TileMap::vOnClick()
{
    // do nothing
}
