#include <iostream>
#include "Game.h"
#include "Rectangle.h"

Game::Game()
{
    renderer = nullptr;
    running = true;
    lastFrameTime = 0;
    m_objectCount = 0;
} 

bool Game::init()
{
    // TODO: create SDL window renderer
    renderer = new Renderer();
    if (!renderer->init())
    {
        return false;
    }
    
    Rectangle * obj1 = new Rectangle(renderer->getSDLRenderer(), 100, 100);
    registerObject(obj1);
    
    return true;
}

void Game::update()
{
    // Update game objects
    for (int i = 0; i < m_objectCount; i++)
    {
        GameObject * obj = reinterpret_cast<GameObject*>(m_objects[i]);
        if (obj != nullptr)
        {
            obj->update();
        }
    }
}

// TODO: dont need to check for null
void Game::render()
{
    // Clear the screen
    if (renderer != nullptr)
    {
        renderer->clear();
    }
    
    // Render game objects
    for (int i = 0; i < m_objectCount; i++)
    {
        GameObject * obj = reinterpret_cast<GameObject*>(m_objects[i]);
        if (obj != nullptr)
        {
            obj->render();
        }
    }
    
    //  Present the graphics
    if (renderer != nullptr)
    {
        renderer->present();
    }
}

void Game::destroy()
{
    if (renderer != nullptr)
    {
        renderer->destroy();
    }
    
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
    if (renderer != nullptr)
    {
        return renderer->isRunning();
    }
    return false;
}


