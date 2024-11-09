#include "PhysicsEngine.h"
#include <string.h>

PhysicsEngine::PhysicsEngine()
{
    (void) memset(m_objects, 0, sizeof(m_objects));
    m_objectCount = 0U;
}

bool PhysicsEngine::init()
{
    for (T_UINT16 i = 0U; i < m_objectCount; i++)
    {
        if (m_objects[i] != nullptr)
        {
            bool L_status = m_objects[i]->init();
            if (!L_status)
            {
                return false;
            }
        }
    }
    return true;
}

void PhysicsEngine::update(T_UINT64 dtime)
{
    for (T_UINT16 i = 0U; i < m_objectCount; i++)
    {
        if (m_objects[i] != nullptr)
        {
            m_objects[i]->update(dtime);
        }
    }
    resolveCollisions();
}

void PhysicsEngine::render()
{
    for (T_UINT16 i = 0U; i < m_objectCount; i++)
    {
        if (m_objects[i] != nullptr)
        {
            m_objects[i]->render();
        }
    }
}

void PhysicsEngine::destroy()
{
    delete this;
}

bool PhysicsEngine::registerObject(PhysicsObject * obj)
{
    if ((m_objectCount < MAX_PHYSICS_OBJECTS) &&
        (obj != nullptr))
    {
        m_objects[m_objectCount] = obj;
        m_objectCount++;
        return true;
    }
    return false;
}

// returns true if AABB objects intersect
bool intersects_AABB(t_point obj1_position, t_vector obj1_size,
    t_point obj2_position, t_vector obj2_size)
{
    if (obj1_position.x + obj1_size.x <= obj2_position.x ||  // left
        obj1_position.x >= obj2_position.x + obj2_size.x ||  // right
        obj1_position.y + obj1_size.y <= obj2_position.y ||  // above 
        obj1_position.y >= obj2_position.y + obj2_size.y)    // below
    {
        return false; // AABB objects do not intersect
    }
    else
    {
        return true; // AABB objects intersect 
    }
}

// TODO: this does not work lol
// obj 1 remains stationary, push obj 2 out of intersection and return the new location of obj2
t_point resolve_AABB(t_point obj1_position, t_vector obj1_size,
    t_point obj2_position, t_vector obj2_size)
{
    t_vector diff = Vector2::subtract(obj1_position, obj2_position);
    T_INT32 x_overlap = (diff.x <= 0) ? diff.x + obj1_size.x : diff.x + obj2_size.x;
    T_INT32 y_overlap = (diff.y <= 0) ? diff.y + obj1_size.y : diff.y + obj2_size.y; 
    
    if (std::abs(x_overlap) <= std::abs(y_overlap))
    {
        return {obj2_position.x + x_overlap, obj2_position.y};
    }
    else
    {
        return {obj2_position.x, obj2_position.y + y_overlap};
    }
}

// returns true if there was a collision
bool PhysicsEngine::resolve(PhysicsObject * obj1, PhysicsObject * obj2)
{
    bool L_retVal = false;
    if (obj1 && obj2 && obj1 != obj2)
    {
        // objects only collide if both are solid
        if (obj1->isSolid() && obj2->isSolid())
        {
            // check if the AABB objects intersect, sharing one touching pixel is ok 
            L_retVal = intersects_AABB(
                obj1->getPosition(), obj1->getSizePixels(), 
                obj2->getPosition(), obj2->getSizePixels()
            );
            
            // if objects intersect, resolve collision
            if (L_retVal)
            {
                if(obj1->getTempWeight() >= obj2->getTempWeight())
                {
                    // obj1 is heavier, so move obj2 using obj1's weight
                    obj2->resolve(obj1->getPosition(), obj1->getSizePixels());
                    obj2->setTempWeight(obj1->getTempWeight()); 
                }
                else
                {
                    // obj2 is heavier, so move obj1 using obj2's weight
                    obj1->resolve(obj2->getPosition(), obj2->getSizePixels());
                    obj1->setTempWeight(obj2->getTempWeight()); 
                }
            }
        }
        else
        {
            L_retVal = false; // at least one object is not solid
        }
    }
    else
    {
        L_retVal = false; // obj cannot collide with itself or a nullptr 
    }
    return L_retVal;
}


void PhysicsEngine::resolveCollisions()
{
    const int maxPasses = 5; // Max passes to avoid infinite loops
    bool collisionResolved;

    for (int pass = 0; pass < maxPasses; ++pass) {
        collisionResolved = true;

        for (int i = 0; i < m_objectCount; ++i) {
            for (int j = i + 1; j < m_objectCount; ++j) {
                
                // if collision happened, need to recheck everything
                if (resolve(m_objects[i], m_objects[j]))
                    collisionResolved = false; 
            
            }
        }

        // if (pass == maxPasses - 1)
        //     printf("max passes\n");

        if (collisionResolved) break; // Exit if no more collisions
    }

    for (int i = 0; i < m_objectCount; ++i) {
        PhysicsObject * obj1 = dynamic_cast<PhysicsObject*>(m_objects[i]);
        if (obj1)
        {
            obj1->resetTempWeight();
        }
    }
}

void PhysicsEngine::vOnClick()
{
    // do nothing
}
