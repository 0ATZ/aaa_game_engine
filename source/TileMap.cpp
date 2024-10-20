#include "TileMap.h"
#include <cstring>

TileMap::TileMap(TileSet * tileSet, t_tilemap tileMap)
{
    m_tileSet = tileSet;
    (void) memcpy(m_tileMap, tileMap, sizeof(t_tilemap));
}

void TileMap::render()
{
    t_point point = {32,32};
    m_tileSet->renderTile(m_tileMap[0], point, SCALE_DOUBLE);
}
