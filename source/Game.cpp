#include <iostream>
#include "Game.h"
#include "Rectangle.h"
#include "ViewPort.h"
#include "sprite/TestMap.h"
#include "Vector2.h"

t_point g_player_pos;
t_point g_camera_pos;

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
    window = new GameWindow(800, 640);
    if (!window->init())
    {
        return false;
    }
    
    t_tile black_square = {0};
    t_tile white_square = {0};
    t_tile baby_blue_square = {0};
    t_tile baby_orange_square = {0};
    for (int i = 0; i < TILE_SIZE; i++)
    {
        white_square[i] = 0xFFFFU;
        baby_blue_square[i] = 0x8ebdU;
        baby_orange_square[i] = 0xedcfU;
    }
    m_tileSet = new TileSet(window);
    m_tileSet->addTile(&black_square);       // 0
    m_tileSet->addTile(&white_square);       // 1
    m_tileSet->addTile(&baby_blue_square);   // 2
    m_tileSet->addTile(&baby_orange_square); // 3

    T_UINT16 tilemap_rows = 32U;
    T_UINT16 tilemap_cols = 32U;
    t_tilemap checker_map = {0};
    for (int i = 0; i < (tilemap_rows * tilemap_cols); i++)
    {
        // ... idk trial and error
        checker_map[i] = ((i % 4) + (i / tilemap_cols)) % 4;
    }

    m_tileMap = new TileMap(m_tileSet, checker_map, tilemap_rows, tilemap_cols);

    registerObject(m_tileMap);

    std::cout << "TileSet count: " << m_tileSet->getTileCount() << std::endl;
    
    // use the rectangle as the player object!
    m_player = new Rectangle(window, 32, 32);
    registerObject(m_player);

    m_viewPort = new ViewPort((PhysicsObject*)m_player, 800, 640);
    
    return true;
}

void Game::update()
{
    // window should update first to get new window state such as user inputs
    window->update();

    // Update the player
    // m_player->update();
    m_viewPort->update();
    t_vector cameraVector = Vector2::invert(m_viewPort->getPositionAsVector());
    bool cameraLocked = ((ViewPort*)m_viewPort)->isCameraLocked();

    // t_point pp = ((PhysicsObject*) m_player)->getCenterPosition();
    // t_point vp = ((PhysicsObject*) m_viewPort)->getCenterPosition();
    // t_point tm = ((PhysicsObject*) m_tileMap)->getPosition();

    // std::cout << "Camera x : " << vp.x << ", " << vp.y << std::endl;
    // std::cout << "Player x : " << pp.x << ", " << pp.y << std::endl;
    // std::cout << "Camera Vec : " << cameraVector.x << ", " << cameraVector.y << std::endl;
    // std::cout << "TileMap    : " << tm.x << ", " << tm.y << std::endl;
    

    // Update all other game objects
    for (int i = 0; i < m_objectCount; i++)
    {
        GameObject * obj = reinterpret_cast<GameObject*>(m_objects[i]);
        if (obj != nullptr)
        {
            obj->update();
            if (!cameraLocked)
            {
                obj->movePosition(cameraVector);
            }
        }
    }
}

void Game::render()
{
    // Clear the window before rendering new graphics
    window->clear();
    
    m_viewPort->render();

    // Render game objects
    for (int i = 0; i < m_objectCount; i++)
    {
        GameObject * obj = reinterpret_cast<GameObject*>(m_objects[i]);
        if (obj != nullptr)
        {
            obj->render();
        }
    }

    // render the player last
    // m_player->render();

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


