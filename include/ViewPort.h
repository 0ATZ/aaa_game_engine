#include "GameTypes.h"
#include "GameObject.h"
#include "PhysicsObject.h"

class ViewPort : public PhysicsObject
{
    public:
        ViewPort(t_vector size);
        bool init();
        void update();
        void render();
        void destroy();
        
        void trackPosition(t_point *position);
        bool isTrackingPosition();
        void vResolveCollision(PhysicsObject * obj);

    private:
        t_point maxPlayerPosition();
        t_point minPlayerPosition();

        t_point * m_trackPosition;
};
