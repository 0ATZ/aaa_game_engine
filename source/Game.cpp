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
    
    return true;
}

void Game::update()
{
    // window should update first to get new window state such as user inputs
    window->update();

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
    // Clear the window before rendering new graphics
    window->clear();
    
    // Render game objects
    for (int i = 0; i < m_objectCount; i++)
    {
        GameObject * obj = reinterpret_cast<GameObject*>(m_objects[i]);
        if (obj != nullptr)
        {
            obj->render();
        }
    }

    // Present the game window after all game objects have been rendered 
    window->render();
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


