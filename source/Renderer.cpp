#include "Renderer.h"
#include <iostream>

Renderer::Renderer() 
{
    m_objectCount = 0;
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

bool Renderer::registerObject(Rectangle * rectangle)
{
    if ((rectangle != nullptr) && (m_objectCount < MAX_OBJECTS))
    {
        m_objects[m_objectCount] = rectangle;
        m_objectCount++;
        return true;
    }
    return false;
}

void Renderer::render()
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); // White background
    SDL_RenderClear(renderer);
    
    // Add game objects here
    for (int i = 0; i < m_objectCount; i++)
    {
        Rectangle * ptr = reinterpret_cast<Rectangle*>(m_objects[i]);
        if (ptr != nullptr)
        {
            ptr->render(renderer);
        }
    }
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
