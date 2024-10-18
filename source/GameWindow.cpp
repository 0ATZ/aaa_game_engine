#include "GameWindow.h"
#include <iostream>

GameWindow::GameWindow() 
{
    m_running = false;
    m_pKeys = 0U;
    m_nextTexture = 0U;

    // Clear out the texture cache pointers
    for (int i = 0; i < MAX_TEXTURES; ++i) {
        m_textureCache[i] = nullptr;
    }
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

        // TODO: handle screen lose focus and gain focus event
        //   clear keys on lose focus, save current state to back buffer
        //   on gain focus, check current keys states
        //   set key states in back buffer, then swap back buffer to front
        // std::cout << m_pKeys << std::endl;
    }
}

T_UINT16 GameWindow::getPlayerKeys()
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

T_UINT16 GameWindow::createTexture(T_UINT16 *pixels, T_UINT16 width, T_UINT16 height)
{
    T_UINT16 L_retVal = 0xFFFFU;
    if (m_nextTexture < MAX_TEXTURES)
    {
        // TODO: check the width and height against max texture size values
        //   maybe max texture is 16x16, 32x32, etc ... or the screen size
        SDL_Texture * L_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB565, SDL_TEXTUREACCESS_STATIC, width, height);

        if (!L_texture)
        {
            SDL_Log("Failed to create texture: %s", SDL_GetError());
        }
        else
        {
            // Update the texture with the pixel data
            SDL_UpdateTexture(L_texture, nullptr, pixels, width * sizeof(T_UINT16));
            m_textureCache[m_nextTexture] = L_texture;
            L_retVal = m_nextTexture;
            m_nextTexture++;
        }

    }
    else
    {
        std::cout << "ERROR: could not allocate texture." << std::endl;
    }

    // return the index for the cached texture
    // if the texture could not be allocated, then return an invalid index (0xFFFF)
    return L_retVal;
}

void GameWindow::renderSprite(T_UINT16 textureID, T_UINT16 x, T_UINT16 y, T_UINT16 width, T_UINT16 height)
{
    if ((textureID < MAX_TEXTURES) && (m_textureCache[textureID]))
    {
        SDL_Rect destRect = { x, y, width, height };
        SDL_RenderCopy(renderer, m_textureCache[textureID], nullptr, &destRect);
    }
    else
    {
        std::cout << "ERROR: Texture out of bounds." << std::endl;
    }
}


// scale can be 1-4 inclusive
void GameWindow::renderScaledSprite(T_UINT16 textureID, T_UINT16 x, T_UINT16 y, T_UINT16 width, T_UINT16 height, T_UINT16 scale)
{
    if ((scale > 0 && scale < 5) && (textureID < MAX_TEXTURES) && (m_textureCache[textureID]))
    {
        SDL_Rect destRect = { x, y, width*scale, height*scale };
        SDL_RenderCopy(renderer, m_textureCache[textureID], nullptr, &destRect);
    }
    else
    {
        std::cout << "ERROR: Texture out of bounds." << std::endl;
    }
}