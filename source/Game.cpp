#include <iostream>
#include "Game.h"
#include "Rectangle.h"
#include "sprites/TestMap.h"

Game::Game()
{
    window = nullptr;
    running = true;
    m_objectCount = 0;
    m_tileSet = nullptr;
    m_tileMap = nullptr;
}

bool Game::init()
{
    window = new GameWindow();
    if (!window->init())
    {
        return false;
    }
    
    t_tile black_square = {0};
    t_tile green_square = {0};
    for (int i = 0; i < TILE_SIZE; i++)
        green_square[i] = 0x07E0U;
    m_tileSet = new TileSet(window);
    m_tileSet->addTile(&black_square);
    m_tileSet->addTile(&green_square);
    m_tileMap = new TileMap(m_tileSet, TEST_MAP_16x16);

    registerObject(m_tileMap);

    std::cout << "TileSet count: " << m_tileSet->getTileCount() << std::endl;
    
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


