#ifndef PHYSICSENGINE_h
#define PHYSICSENGINE_h

#include "GameObject.h"
#include "PhysicsObject.h"

class PhysicsEngine : public GameObject
{
    public:
        PhysicsEngine();
        bool init();
        void update(T_UINT64 dtime);
        void render();
        void destroy();

        bool registerObject(PhysicsObject *obj);
        void resolveCollisions();

        void vOnClick();

    private:
        static const T_UINT64 MAX_PHYSICS_OBJECTS = 64U;
        PhysicsObject * m_objects[MAX_PHYSICS_OBJECTS];
        T_UINT16 m_objectCount;
};

#endif
