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

void PhysicsEngine::resolveCollisions()
{
    const int maxPasses = 5; // Max passes to avoid infinite loops
    bool collisionResolved;

    for (int pass = 0; pass < maxPasses; ++pass) {
        collisionResolved = true;

        for (int i = 0; i < m_objectCount; ++i) {
            for (int j = i + 1; j < m_objectCount; ++j) {
                PhysicsObject * obj1 = dynamic_cast<PhysicsObject*>(m_objects[i]);
                PhysicsObject * obj2 = dynamic_cast<PhysicsObject*>(m_objects[j]);
                if (obj1 && obj2 && obj1 != obj2 && 
                    obj1->isSolid() && obj2->isSolid() &&
                    obj1->intersects(obj2->getPosition(), obj2->getSizePixels()) && 
                    !obj1->isTouching(obj2->getPosition(), obj2->getSizePixels())) 
                {
                    if (obj1->getTempWeight() >= obj2->getTempWeight())
                    {
                        // move object 2 with object 1 weight
                        obj2->resolve(obj1->getPosition(), obj1->getSizePixels());
                        obj2->setTempWeight(obj1->getTempWeight());
                    }
                    else
                    {
                        // move object 1 with object 2 weight
                        obj1->resolve(obj2->getPosition(), obj2->getSizePixels());
                        obj1->setTempWeight(obj2->getTempWeight());
                    }
                    collisionResolved = false;
                }
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
