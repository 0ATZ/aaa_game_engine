#include <SDL2/SDL.h>
#include <iostream>
#include "Game.h"

Game::Game()
{
    renderer = nullptr;
    running = true;
    lastFrameTime = 0;
} 

bool Game::init()
{
    renderer = new Renderer();
    if (!renderer->init())
    {
        return false;
    }
    return true;
}

void Game::run()
{
    Uint32 frameDuration = 1000 / 60; // Frame duration for 60 FPS

    while (renderer->isRunning()) {
        Uint32 startTime = SDL_GetTicks();
        update();
        render();
        Uint32 frameTime = SDL_GetTicks() - startTime;
        if (frameDuration > frameTime) {
            SDL_Delay(frameDuration - frameTime);
        }
    }
}

void Game::cleanUp()
{
    if (renderer) {
        renderer->destroy();
    }
}

void Game::update()
{
    // Update game logic here
}

//TODO: would rather just not start up if renderer is NULL
void Game::render()
{
    if (renderer) 
    {
        renderer->render();
    }
}


