#ifndef PHYSICSOBJECT_H 
#define PHYSICSOBJECT_H 

#include "GameTypes.h"
#include "GameObject.h"
#include "Sprite.h"

class PhysicsObject : public GameObject
{
    public:
        PhysicsObject();
        PhysicsObject(T_INT32 x, T_INT32 y, T_UINT16 widthPx, T_UINT16 heightPx, T_UINT16 weight);

        bool init();
        void update(T_UINT64 dtime);
        void render();
        void destroy();

        bool detectCollision(PhysicsObject *obj);

        // derived classes can perform custom actions on collision 
        virtual void vResolveCollision(PhysicsObject * obj) = 0;
        
        void setWeight(T_UINT16 weight);
        T_UINT16 getWeight();
        bool isSolid();
        
        static const T_UINT16 WEIGHT_STATIC = 0xFFFFU;
    
    // TODO: perform physics calculations to move position
    // TODO: calculate collisions
    protected:
        
        // resolve the position of the object 
        void resolveCollision(PhysicsObject *obj);

        T_UINT32 m_speedPx; // pixels per frame
        t_vector m_direction;
        bool m_solid;
        T_UINT16 m_weight;
        
};

#endif

