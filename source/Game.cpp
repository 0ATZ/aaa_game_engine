#include <SDL2/SDL.h>
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
    // TODO: move SDL renderer logic back into the game class
    renderer = new Renderer();
    if (!renderer->init())
    {
        return false;
    }
    
    Rectangle * obj1 = new Rectangle(100, 100);
    renderer->registerObject(obj1);
    registerObject(obj1);
    
    return true;
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

// TODO: move the game loop into the main function
void Game::run()
{
    Uint32 frameDuration = 1000 / 60; // Frame duration for 60 FPS

    while (renderer->isRunning())
    {
        Uint32 startTime = SDL_GetTicks();
        update();
        render();
        Uint32 frameTime = SDL_GetTicks() - startTime;
        if (frameDuration > frameTime) {
            SDL_Delay(frameDuration - frameTime);
        }
    }
}

// TODO: dont need to check for null
void Game::cleanUp()
{
    if (renderer)
    {
        renderer->destroy();
    }
}

// TODO: dont need to check for null
void Game::update()
{
    for (int i = 0; i < m_objectCount; i++)
    {
        Rectangle * ptr = reinterpret_cast<Rectangle*>(m_objects[i]);
        if (ptr != nullptr)
        {
            ptr->update();
        }
    }
}

void Game::render()
{
    if (renderer) 
    {
        renderer->render();
    }
}


