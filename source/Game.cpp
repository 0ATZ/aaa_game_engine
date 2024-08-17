#include <iostream>
#include "Game.h"

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
    // TODO: create game object base class instead of only rendering rectangles
    for (int i = 0; i < m_objectCount; i++)
    {
        Rectangle * ptr = reinterpret_cast<Rectangle*>(m_objects[i]);
        if (ptr != nullptr)
        {
            ptr->update();
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
    // TODO: create game object base class instead of only rendering rectangles
    for (int i = 0; i < m_objectCount; i++)
    {
        Rectangle * ptr = reinterpret_cast<Rectangle*>(m_objects[i]);
        if (ptr != nullptr)
        {
            ptr->render();
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
    
    // TODO: create game object base class instead of only rendering rectangles
    for (int i = 0; i < m_objectCount; i++)
    {
        Rectangle * ptr = reinterpret_cast<Rectangle*>(m_objects[i]);
        if (ptr != nullptr)
        {
            ptr->destroy();
        }
    }
}

bool Game::registerObject(Rectangle * rectangle)
{
    if ((rectangle != nullptr) && (m_objectCount < MAX_OBJECTS))
    {
        m_objects[m_objectCount] = rectangle;
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


