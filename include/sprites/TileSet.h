#ifndef TILESET_H
#define TILESET_H

#include "BaseTypes.h"
#include "GameTypes.h"
#include "SpriteSheet.h"
 
class TileSet : public SpriteSheet
{
    public:
        TileSet(const char *const filename, T_UINT16 tileCount, T_UINT16 tileSize);

        t_vector getTileSize();

    private:
        t_vector m_tileSizePx;
};


#endif