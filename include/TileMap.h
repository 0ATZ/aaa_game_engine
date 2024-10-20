#include "BaseTypes.h"
#include "GameTypes.h"
#include "GameObject.h"
#include "TileSet.h"

class TileMap : public GameObject
{
    public:
        TileMap(TileSet * tileSet, t_tilemap tileMap);
        void render();

    private:
        TileSet * m_tileSet;
        t_tilemap m_tileMap;
        
};