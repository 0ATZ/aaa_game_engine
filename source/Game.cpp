#include <iostream>
#include "GameWindow.h"
#include "Game.h"
#include "Rectangle.h"
#include "ViewPort.h"
#include "sprite/TestMap.h"
#include "Vector2.h"

t_point g_player_pos;
t_point g_camera_pos;

Game::Game()
{
    running = true;
    m_objectCount = 0;
    m_tileSet = nullptr;
    m_tileMap = nullptr;
    m_intersect = false;
}

bool Game::init()
{
    t_vector window_size = {800, 640};
    if (!GameWindow::initialize(window_size))
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
    m_tileSet = new TileSet();
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
    
    m_redSquare = new Tile("./assets/sprites/red_16x16.bin");
    GameWindow::create_texture(m_redSquare);
    m_greenSquare = new Tile("./assets/sprites/green_16x16.bin");
    GameWindow::create_texture(m_greenSquare);

    m_testSquare = new PhysicsObject(128, 128, 64, 64);

    // use the rectangle as the player object!
    m_player = new Rectangle(32, 32);
    registerObject(m_player);

    m_viewPort = new ViewPort((PhysicsObject*)m_player, 800, 640);
    return true;
}

void Game::update()
{
    // window should update first to get new window state such as user inputs
    GameWindow::process_events();
    
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
            // if (!cameraLocked)
            // {
            //     obj->movePosition(cameraVector);
            // }
        }
    }

    if (((PhysicsObject*)m_player)->intersects((PhysicsObject*)m_testSquare))
    {
        m_intersect = true;
    }
    else
    {
        m_intersect = false;
    }
}

void Game::render()
{
    // Clear the window before rendering new graphics
    GameWindow::clear_window();
    
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

    if (m_intersect)
        GameWindow::render_sprite(m_redSquare, {128, 128}, {64, 64});
    else
        GameWindow::render_sprite(m_greenSquare, {128, 128}, {64, 64});
    
    // render the player last
    // m_player->render();

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


