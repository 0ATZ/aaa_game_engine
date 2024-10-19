#include "TileMap.h"

TileMap::TileMap(T_UINT8 * tileMap, T_UINT16 width, T_UINT16 height, T_UINT16 tileSize)
{
    m_tileMap = tileMap;
    m_width = width;
    m_height = height;
    m_tileSize = tileSize;
}
