#include "TileSet.h"
#include "GameWindow.h"
#include <iostream>


TileSet::TileSet(const char * const filename, T_UINT16 tileCount, T_UINT16 tileSize) :
    SpriteSheet(filename, tileCount, tileSize, tileSize)
{
    m_tileSizePx = {tileSize, tileSize};
}

t_vector TileSet::getTileSize()
{
    return m_tileSizePx;
}
