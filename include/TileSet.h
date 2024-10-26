#ifndef TILESET_H
#define TILESET_H

#include "BaseTypes.h"
#include "GameTypes.h"
#include "Tile.h"
 
class TileSet
{
    public:
        TileSet();
        TileSet(t_tileset tileSet);

        t_index addTile(t_tile *tilePixels);
        Tile *getTileFromID(t_index tileID);
        
        T_UINT16 getTileCount();
        bool hasSpace();
        bool isValid(t_index tileID);

    private:

        T_UINT16 m_tileCount;  // number of tiles added to the tileset
        Tile * m_tileSet[TILESET_SIZE]; // pointers 

};


#endif