#ifndef TILESET_H
#define TILESET_H

#include "BaseTypes.h"
#include "GameTypes.h"
#include "GameWindow.h"
#include "Tile.h"

// TODO: implement delete tile? 
class TileSet
{
    public:
        TileSet(GameWindow * window);
        TileSet(GameWindow * window, t_tileset tileSet);

        t_index addTile(t_tile *tilePixels);
        void renderTile(t_index tileID, t_point point, t_scale scale);

        bool hasSpace();
        bool isValid(t_index tileID);

    private:

        T_UINT16 m_tileCount;  // number of tiles added to the tileset
        GameWindow * m_window; // Game window used to create the textures
        Tile * m_tileSet[TILESET_SIZE]; // pointers 

};


#endif