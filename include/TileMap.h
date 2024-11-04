#include "BaseTypes.h"
#include "GameTypes.h"
#include "GameObject.h"
#include "TileSet.h"

class TileMap : public GameObject
{
    public:
        TileMap(const char *const filename, TileSet *tileSet, T_UINT16 numRows, T_UINT16 numCols);
        void render();
        bool init();
        void update(T_UINT64 dtime);
        void destroy();
        void vOnClick();

    private:
        TileSet * m_tileSet;
        T_UINT8 * m_tileMap;

        // t_vector m_scale; 
        t_vector m_scaledTileSize;
        T_UINT16 m_numRows;
        T_UINT16 m_numCols;
        T_UINT32 m_numTiles;
        
        t_index getTileID(T_UINT16 row, T_UINT16 col);
        t_point tilePosition(T_UINT16 row, T_UINT16 col);
};