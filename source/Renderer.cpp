#include "Renderer.h"
#include <iostream>

Renderer::Renderer()
{
    xpos=0;
    ypos=0;
}

bool Renderer::init()
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

void Renderer::render()
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); // White background
    SDL_RenderClear(renderer);

    // Draw game objects here
    xpos = (xpos + 1) % (800-100);
    ypos = (ypos + 1) % (600-100);
    renderRectangle(xpos, ypos);

    SDL_RenderPresent(renderer);
}

void Renderer::destroy()
{
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

bool Renderer::isRunning()
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            return false;
        }
    }
    return true;
}

void Renderer::renderRectangle(int x, int y)
{
    // Define the rectangle
    SDL_Rect fillRect = { x, y, 100, 100 }; // x, y, width, height

    // Draw the filled rectangle
    SDL_RenderFillRect(renderer, &fillRect);

    // Optionally, draw the outline of the rectangle
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF); // Black outline
    SDL_RenderDrawRect(renderer, &fillRect);
}
