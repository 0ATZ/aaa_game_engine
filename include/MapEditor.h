#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include "TileMap.h"

class MapEditor : public TileMap
{
    public: 
        MapEditor(const char * const filename, TileSet * tileSet, T_UINT16 numRows, T_UINT16 numCols);
        ~MapEditor();
        void update(T_UINT64 dtime);
        void render();
        void vOnClick();
        
        t_vector getRowCol(t_point point);
        bool saveMapFile();

    private:
        static const T_UINT32 MAX_FILENAME_LENGTH = 128UL;
        T_CHAR m_filename[MAX_FILENAME_LENGTH];

        t_index m_tileIndex;
        bool m_pressed;
        T_UINT16 m_prevKeys;

};


#endif