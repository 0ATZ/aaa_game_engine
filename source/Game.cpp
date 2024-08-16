#include <SDL2/SDL.h>
#include <iostream>
#include "Game.h"

Game::Game()
{
    window = nullptr;
    renderer = nullptr;
    running = true;
    lastFrameTime = 0;
} 

bool Game::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("SDL2 Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    return true;
}

void Game::run()
{
    Uint32 frameDuration = 1000 / 60; // Frame duration for 60 FPS

    while (running) {
        Uint32 startTime = SDL_GetTicks();
        handleEvents();
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
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}


void Game::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
    }
}

void Game::update()
{
    // Update game logic here
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); // White background
    SDL_RenderClear(renderer);

    // Draw game objects here
    x_pos = (x_pos + 1) % (800-100);
    y_pos = (y_pos + 1) % (600-100);
    renderRectangle(x_pos, y_pos);

    SDL_RenderPresent(renderer);
}

void Game::renderRectangle(int x, int y)
{
    // Define the rectangle
    SDL_Rect fillRect = { x, y, 100, 100 }; // x, y, width, height

    // Draw the filled rectangle
    SDL_RenderFillRect(renderer, &fillRect);

    // Optionally, draw the outline of the rectangle
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF); // Black outline
    SDL_RenderDrawRect(renderer, &fillRect);
}
