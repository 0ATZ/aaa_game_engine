#include "GameTypes.h"
#include "GameObject.h"
#include "PhysicsObject.h"

class ViewPort : public PhysicsObject
{
    public:
        ViewPort(PhysicsObject * player, T_UINT16 widthPixels, T_UINT16 heightPixels);
        bool init();
        void update();
        void render();
        void destroy();
        
        bool isCameraLocked();
        bool isObjectVisible(GameObject *obj);
        void centerToPlayer();

    private:
        PhysicsObject * m_player;  
        t_point maxPlayerPosition();
        t_point minPlayerPosition();

        bool m_followPlayer;
};
