#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include "TileMap.h"

class MapEditor : public TileMap
{
    public: 
        MapEditor(const char * const filename, TileSet * tileSet, T_UINT16 numRows, T_UINT16 numCols);
        void update(T_UINT64 dtime);
        void render();
        void vOnClick();
        
        t_vector getRowCol(t_point point);

    private:
        t_index m_tileIndex;
        bool m_pressed;

};


#endif