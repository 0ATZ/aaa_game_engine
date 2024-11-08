#include <iostream>
#include "GameWindow.h"
#include "Game.h"
#include "Rectangle.h"
#include "ViewPort.h"
#include "Vector2.h"
#include "TestBox.h"
#include "Cursor.h"
#include "MapEditor.h"

t_point g_player_pos;
t_point g_camera_pos;

Game::Game()
{
    running = true;
    m_objectCount = 0U;
    m_tileSet = nullptr;
    // m_tileMap = nullptr;
    m_intersect = false;
}

bool Game::init()
{
    t_vector window_size = {800, 640};
    if (!GameWindow::initialize(window_size))
    {
        return false;
    }
    GameWindow::set_viewport_mode(VIEW_FOLLOW_PLAYER_DYNAMIC);
    
    m_tileSet = new TileSet("./assets/sprites/grass_sprites.bin", 36, 16);

    registerObject(new MapEditor("./assets/tilemaps/testmap.bin", m_tileSet, 32U, 32U));
    registerObject(new TestBox({100,100}, 100U, 100U));   // default lighter than player
    registerObject(new TestBox({500,500}, 75U, 50U));     // default lighter than player
    registerObject(new TestBox({400,200}, 50U, 50U, 12)); // slightly too heavy to move
    registerObject(new TestBox({100,400}, 50U, 50U));
    
    // use the rectangle as the player object!
    m_player = new Rectangle(32, 32);
    registerObject(m_player);
    
    TestBox * stationary_box = new TestBox({210, 300}, 50U, 50U);
    stationary_box->setSpeed(0U);
    registerObject(stationary_box);
    
    registerObject(new TestBox({100,300}, 100U, 20U, PhysicsObject::WEIGHT_STATIC)); // cannot be moved by anything
    m_cursor = new Cursor();
    return true;
}
void resolveCollisions(GameObject ** objects, int numObjects);

void Game::update(T_UINT64 dtime)
{
    // window should update first to get new window state such as user inputs
    GameWindow::process_events();
    
    // Update all other game objects
    for (int i = 0; i < m_objectCount; i++)
    {
        GameObject * obj = reinterpret_cast<GameObject*>(m_objects[i]);
        if (obj != nullptr)
        {
            obj->update(dtime);
        }
    }

    // detect and resolve each game object pair for collision
    resolveCollisions(m_objects, m_objectCount);

    // detect and resolve click events
    m_cursor->update(dtime);
    if (((Cursor*) m_cursor)->isClicked())
    {
        for (int i = 0; i < m_objectCount; i++)
        {
            // call the onClick method if obj intersects with cursor 
            ((Cursor*) m_cursor)->processClick(m_objects[i]);
        }
    }

    // move the viewable area based on the player position 
    GameWindow::update_viewport(dtime, m_player->getCenter());
}

void resolveCollisions(GameObject ** objects, int numObjects) {
    const int maxPasses = 5; // Max passes to avoid infinite loops
    bool collisionResolved;

    for (int pass = 0; pass < maxPasses; ++pass) {
        collisionResolved = true;

        for (int i = 0; i < numObjects; ++i) {
            for (int j = i + 1; j < numObjects; ++j) {
                PhysicsObject * obj1 = dynamic_cast<PhysicsObject*>(objects[i]);
                PhysicsObject * obj2 = dynamic_cast<PhysicsObject*>(objects[j]);
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

        if (pass == maxPasses - 1)
            printf("max passes\n");

        if (collisionResolved) break; // Exit if no more collisions
    }

    for (int i = 0; i < numObjects; ++i) {
        PhysicsObject * obj1 = dynamic_cast<PhysicsObject*>(objects[i]);
        if (obj1)
        {
            obj1->resetTempWeight();
        }
    }
}

void Game::render()
{
    // Clear the window before rendering new graphics
    GameWindow::clear_window();
    
    // Render game objects
    for (int i = 0; i < m_objectCount; i++)
    {
        GameObject * obj = m_objects[i];
        if (obj != nullptr)
        {
            obj->render();
        }
    }

    // Present the game window after all game objects have been rendered 
    GameWindow::present_window();
}

void Game::destroy()
{
    GameWindow::destroy();
    
    for (int i = 0; i < m_objectCount; i++)
    {
        GameObject * obj = reinterpret_cast<GameObject*>(m_objects[i]);
        if (obj != nullptr)
        {
            obj->destroy();
        }
    }
}

bool Game::registerObject(GameObject * obj)
{
    if ((obj != nullptr) && (m_objectCount < MAX_OBJECTS))
    {
        m_objects[m_objectCount] = obj;
        m_objectCount++;
        return true;
    }
    return false;
}

bool Game::isRunning()
{
    return GameWindow::is_running();
}


