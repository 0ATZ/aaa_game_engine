#include "GameTypes.h"
#include "GameObject.h"
#include "PhysicsObject.h"

class ViewPort : public PhysicsObject
{
    public:
        ViewPort(t_vector size);
        bool init();
        void update(T_UINT64 dtime);
        void render();
        void destroy();
        
        void setPlayerPosition(t_point playerPosition);
        void setMode(t_viewport_mode mode);
        void vResolveCollision(PhysicsObject * obj);
        void vOnClick();

    private:
        t_point maxPlayerPosition();
        t_point minPlayerPosition();

        t_point m_playerPosition;
        t_viewport_mode m_viewportMode;
};
