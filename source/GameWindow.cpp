#include "GameWindow.h"
#include <iostream>

GameWindow::GameWindow() 
{
    m_running = false;
    m_pKeys = 0U;
}

bool GameWindow::init()
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
    
    m_running = true;
    return true;
}

/* 
 * merge keypresses into a 16 bits: 
 * 0x01: W (up)
 * 0x02: S (down)
 * 0x04: A (left)
 * 0x08: D (right)
 * 0x10: jump
 * 0x20: shift
 */
void GameWindow::update()
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT) 
        {
            m_running = false;
        }
        else if (event.type == SDL_KEYDOWN)
        {
            // activate the corresponding bit
            int keyCode = event.key.keysym.sym;
            if (keyCode == SDLK_w)
                m_pKeys |= UP;
            if (keyCode == SDLK_s)
                m_pKeys |= DOWN;
            if (keyCode == SDLK_a)
                m_pKeys |= LEFT;
            if (keyCode == SDLK_d)
                m_pKeys |= RIGHT;
        }
        else if (event.type == SDL_KEYUP)
        {
            // deactivate the corresponding bit
            int keyCode = event.key.keysym.sym;
            if (keyCode == SDLK_w)
                m_pKeys &= (~UP);
            if (keyCode == SDLK_s)
                m_pKeys &= (~DOWN);
            if (keyCode == SDLK_a)
                m_pKeys &= (~LEFT);
            if (keyCode == SDLK_d)
                m_pKeys &= (~RIGHT);
        }
        // std::cout << m_pKeys << std::endl;
    }
}

uint16_t GameWindow::getPlayerKeys()
{
    return m_pKeys;
}

void GameWindow::render()
{
    SDL_RenderPresent(renderer);
}

void GameWindow::destroy()
{
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

void GameWindow::clear()
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); // White background
    SDL_RenderClear(renderer);
}

SDL_Renderer * GameWindow::getSDLRenderer()
{
    return renderer;
}

bool GameWindow::isRunning()
{
    return m_running;
}
