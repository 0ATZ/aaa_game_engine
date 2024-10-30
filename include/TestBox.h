#ifndef TESTBOX_H
#define TESTBOX_H


#include "GameTypes.h"
#include "PhysicsObject.h"

class TestBox : public PhysicsObject
{
    public:
        TestBox(t_point position, T_UINT16 width, T_UINT16 height);
        TestBox(t_point position, T_UINT16 width, T_UINT16 height, bool isStatic);

        void update(T_UINT64 dtime);
        void render();
        void resolveCollision(GameObject *obj);

    private:
        bool m_activated;
        T_UINT64 m_timer;
};


#endif
