#include "BaseTypes.h"
#include "GameTypes.h"
#include "GameObject.h"
#include "TileSet.h"

class TileMap : public GameObject
{
    public:
        TileMap(TileSet * tileSet, t_tilemap tileMap, T_UINT16 numRows, T_UINT16 numCols);
        void render();
        bool init() { return true; };
        void update() {}; // TODO: maybe need to process camera position or something?
        void destroy();

    private:
        TileSet * m_tileSet;
        t_tilemap m_tileMap;
        t_scale m_scale; 
        T_UINT16 m_numRows;
        T_UINT16 m_numCols;
        T_UINT32 m_numTiles;
        
        t_index getTileID(T_UINT16 row, T_UINT16 col);
        t_point tilePosition(T_UINT16 row, T_UINT16 col);
};