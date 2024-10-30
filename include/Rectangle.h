#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "PhysicsObject.h"
#include "Tile.h"

class Rectangle: public PhysicsObject
{
    public:
        Rectangle(int pixelWidth, int pixelHeight);
        
        bool init();
        void update(T_UINT64 dtime);
        void render();
        void destroy();

        void vResolveCollision(PhysicsObject * obj);
    
};
#endif
