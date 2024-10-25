#include "PhysicsObject.h"
#include <cstdlib>

PhysicsObject::PhysicsObject()
{
    m_position = {0L, 0L};
    m_sizePx = {0L, 0L};  // TODO: how to calc collisions
    m_velocityPx = {0L, 0L};
    m_sprite = nullptr;
}

PhysicsObject::PhysicsObject(T_INT32 x, T_INT32 y, T_UINT16 widthPx, T_UINT16 heightPx)
{
    m_position = { x, y };
    m_sizePx = { widthPx, heightPx };
    m_velocityPx = {0L, 0L};
    m_sprite = nullptr;
}


// position, width, and height define a 2D rectangular mesh, 
// which represents the 2D space occupied by this object
// the 2D rectangular mesh can be used to calculate collisions 
// 
// p is the upper left coordinate of the rectangle, 
//      w is the width, and h is the height
//
//     (p.x, p.y) o--------------o (p.x + w, p.y)
//                |              |
//                |              |
//                |              | h
//                |              |
//                |              |
// (p.x, p.y + h) o--------------o (p.x + w, p.y + h) 
//                       w
bool PhysicsObject::intersects(GameObject * obj)
{
    if (obj != nullptr)
    {
        // Calculate 2 dimensional overlap
        t_point objPos = obj->getPosition();
        t_vector objSize = obj->getSizePixels();
        T_INT32 dx = objPos.x - m_position.x;
        T_INT32 dy = objPos.y - m_position.y;

        // check if x values are close enough to collide
        if ((dx > 0) && (dx <= m_sizePx.x) ||      // this is to the left of obj, and x can collide
            (dx < 0) && (abs(dx) <= objSize.x) ||  // obj is to the left of this, and x can collide
            (dx == 0))                             // x vals are the same
        
            // check if y values are close enough to collide
            if ((dy > 0) && (dy <= m_sizePx.y) ||     // this is above obj, and y can collide
                (dy < 0) && (abs(dy) <= objSize.x) || // obj is above this, and y can collide
                (dy == 0))                            // y vals are the same
                
                // both x and y are close enough to collide
                return true;

    }
    
    // either the x position or y positions are too far
    return false;
}

bool PhysicsObject::init()
{
    return true;
}

void PhysicsObject::update()
{
    // TODO: calc collisions
}

void PhysicsObject::render()
{
    // TODO: render the sprite? 
}

void PhysicsObject::destroy()
{
    delete this;
}
