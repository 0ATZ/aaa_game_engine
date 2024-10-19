#include "BaseTypes.h"
#include "GameObject.h"

class TileMap : public GameObject
{
    public:
        TileMap(T_UINT8 * tileMap, T_UINT16 width, T_UINT16 height, T_UINT16 tileSize);
        //void TileMap::render();

    private:
        T_UINT16 m_width;
        T_UINT16 m_height;
        T_UINT16 m_tileSize;
        T_UINT8 * m_tileMap;
        
};