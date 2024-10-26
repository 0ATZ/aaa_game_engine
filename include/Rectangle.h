#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "PhysicsObject.h"
#include "Tile.h"

class Rectangle: public PhysicsObject
{
    public:
        Rectangle(int pixelWidth, int pixelHeight);
        
        bool init();
        void update();
        void render();
        void destroy();
    
};
#endif
