#include <iostream>
#include "GameWindow.h"
#include "Game.h"
#include "Rectangle.h"
#include "ViewPort.h"
#include "sprite/TestMap.h"
#include "Vector2.h"
#include "TestBox.h"

t_point g_player_pos;
t_point g_camera_pos;

Game::Game()
{
    running = true;
    m_objectCount = 0U;
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
    

    // TODO: replace this logic with a spritesheet
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
    
    // m_redSquare = new Tile("./assets/sprites/red_16x16.bin");
    // m_greenSquare = new Tile("./assets/sprites/green_16x16.bin");

    
    registerObject(new TestBox({100,300}, 100U, 10U, true));
    registerObject(new TestBox({100,100}, 100U, 100U));
    registerObject(new TestBox({500,500}, 75U, 50U));
    registerObject(new TestBox({400,200}, 50U, 50U));

    // use the rectangle as the player object!
    m_player = new Rectangle(32, 32);
    registerObject(m_player);

    registerObject(new TestBox({100,400}, 50U, 50U));
    
    return true;
}

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
    for (int i = 0; i < m_objectCount; i ++)
    {
        for (int j = 0; j < m_objectCount; j++)
        {
            if (i != j && m_objects[i]->intersects(m_objects[j]))
            {
                // printf("intersect: %d, %d\n", i, j);
                m_objects[i]->resolveCollision(m_objects[j]);
            }
        }
    }

    GameWindow::center_viewport(m_player->getCenter());
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

    // if (m_intersect)
    //     GameWindow::render_sprite_viewport(m_redSquare, {128, 128}, {64, 64});
    // else
    //     GameWindow::render_sprite_viewport(m_greenSquare, {128, 128}, {64, 64});

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


