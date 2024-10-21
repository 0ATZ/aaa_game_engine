#include "GameTypes.h"
#include "GameObject.h"

class ViewPort : public GameObject
{
    public:
        ViewPort(GameObject * player, T_UINT16 widthPixels, T_UINT16 heightPixels);
        bool init();
        void update();
        void render();
        void destroy();
        
        bool isCameraLocked();
        void centerToPlayer();

    private:
        GameObject * m_player;  
        t_point maxPlayerPosition();
        t_point minPlayerPosition();
        
        bool m_followPlayer;
};
