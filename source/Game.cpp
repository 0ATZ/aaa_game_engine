#include <iostream>
#include "Game.h"
#include "Rectangle.h"

Game::Game()
{
    window = nullptr;
    running = true;
    lastFrameTime = 0;
    m_objectCount = 0;
}

bool Game::init()
{
    window = new GameWindow();
    if (!window->init())
    {
        return false;
    }
    
    Rectangle * obj1 = new Rectangle(window, 100, 100);
    registerObject(obj1);
    
    // Window render update gets called last
    registerObject(window);
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
    // Clear the window
    if (window != nullptr)
    {
        window->clear();
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
}

void Game::destroy()
{
    if (window != nullptr)
    {
        window->destroy();
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
    if (window != nullptr)
    {
        return window->isRunning();
    }
    return false;
}


