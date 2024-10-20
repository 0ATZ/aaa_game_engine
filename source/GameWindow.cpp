#include "GameWindow.h"
#include "Sprites/SquareSprite.h"
#include <iostream>

GameWindow::GameWindow() 
{
    m_running = false;
    m_pKeys = 0U;
    m_nextTexture = 0U;
    
    // initialize SDL video
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    }

    // create the SDL window
    window = SDL_CreateWindow("SDL2 Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }
    
    // create the SDL renderer 
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
}

bool GameWindow::init()
{    
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
        switch (event.type)
        {
            case SDL_QUIT: 
                
                // SDL window closed
                m_running = false;

            case SDL_KEYDOWN:

                // keypress activates the corresponding bit
                switch (event.key.keysym.sym)
                {
                    case SDLK_w:
                        m_pKeys |= UP;
                        break;
                    case SDLK_s:
                        m_pKeys |= DOWN;
                        break;
                    case SDLK_a:
                        m_pKeys |= LEFT;
                        break;
                    case SDLK_d:
                        m_pKeys |= RIGHT;
                        break;
                    default:
                        // nothing
                        break;
                }
            case SDL_KEYUP:

                // keyrelease deactivates the corresponding bit
                switch (event.key.keysym.sym)
                {
                    case SDLK_w:
                        m_pKeys &= (~UP);
                        break;
                    case SDLK_s:
                        m_pKeys &= (~DOWN);
                        break;
                    case SDLK_a:
                        m_pKeys &= (~LEFT);
                        break;
                    case SDLK_d:
                        m_pKeys &= (~RIGHT);
                        break;
                    default:
                        // nothing
                        break;
                }

            case SDL_WINDOWEVENT_FOCUS_LOST:

                m_pKeys = 0U;
            
            case SDL_WINDOWEVENT_FOCUS_GAINED:

                const T_UINT8 * keyState = SDL_GetKeyboardState(nullptr);
                if (keyState[SDL_SCANCODE_W])
                {
                    m_pKeys |= UP;
                }
                if (keyState[SDL_SCANCODE_S])
                {
                    m_pKeys |= DOWN;
                }
                if (keyState[SDL_SCANCODE_A])
                {
                    m_pKeys |= LEFT;
                }
                if (keyState[SDL_SCANCODE_D])
                {
                    m_pKeys |= RIGHT;
                }
        }
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

t_index GameWindow::createTexture(t_pixel *pixels, T_UINT16 width, T_UINT16 height)
{
    t_index L_retVal = 0xFFU;
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
            std::cout << "texture created: " << m_nextTexture << std::endl;
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

t_index GameWindow::createTexture(t_tile *tilePixels)
{
    return this->createTexture((t_pixel*) tilePixels, TILE_WIDTH, TILE_HEIGHT);
}

t_index GameWindow::createTexture(Sprite *sprite)
{
    t_index textureID = this->createTexture(
        sprite->getSpritePixels(),
        sprite->getWidth(),
        sprite->getHeight()
    );

    sprite->setTextureID(textureID);
    return textureID;
}

// scale can be 1-4 inclusive
void GameWindow::renderTexture(t_index textureID, t_point point, T_UINT16 width, T_UINT16 height, t_scale scale)
{
    if (this->textureExists(textureID))
    {
        SDL_Rect destRect = { point.x, point.y, width*scale, height*scale };
        SDL_RenderCopy(renderer, m_textureCache[textureID], nullptr, &destRect);
    }
}

void GameWindow::renderSprite(Sprite *sprite, t_point point, t_scale scale)
{
    // render the sprite 
    // texture must be created beforehand using createTexture(Sprite *sprite)
    this->renderTexture(
        sprite->getTextureID(), 
        point,
        sprite->getWidth(),
        sprite->getHeight(),
        scale
    );
}

bool GameWindow::textureExists(t_index textureID)
{
    if (textureID < m_nextTexture)
    {
        return true;
    }
    return false;
}
