#include "GameTypes.h"
#include "GameObject.h"
#include "GameWindow.h"

class ViewPort : GameObject
{
    public:
        ViewPort(GameWindow * window, GameObject * player, GameObject * map);
        bool init();
        void update();
        void render();
        void destroy();

    private:
        t_point * m_windowSize;
        t_point * m_playerSize;
        t_point * m_mapSize;
        t_point * m_mapPosition;
        t_point * m_playerPosition;
        T_UINT16 m_pKeys;
  
};
