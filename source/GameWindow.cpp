#include "GameWindow.h"
#include <iostream>
#include "ViewPort.h"

namespace GameWindow
{
    extern const T_UINT16 UP;
    extern const T_UINT16 DOWN;
    extern const T_UINT16 LEFT;
    extern const T_UINT16 RIGHT;

    SDL_Window * sdl_window;
    SDL_Renderer * sdl_renderer;
    bool game_running;
    T_UINT16 player_keys;
    t_vector window_size;
    ViewPort * view_port;

    bool initialize(t_vector size)
    {
        bool L_initSuccess = true;
        game_running = false;

        // initialize namespace variables 
        player_keys = 0U;
        window_size = size;
   
        // initialize SDL video
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
            L_initSuccess = false;
        }

        // create the SDL window
        sdl_window = SDL_CreateWindow("SDL2 Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, size.x, size.y, SDL_WINDOW_SHOWN);
        if (sdl_window == nullptr) {
            std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            L_initSuccess = false;
        }
        
        // create the SDL renderer 
        sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (sdl_renderer == nullptr) {
            std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(sdl_window);
            SDL_Quit();
            L_initSuccess = false;
        }
        
        // create the viewport to help render objects at the correct position
        view_port = new ViewPort(window_size);

        // if the init succeeded, game is now running
        game_running = L_initSuccess;

        return L_initSuccess;
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
    void process_events()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0)
        {
            switch (event.type)
            {
                case SDL_QUIT: 
                    
                    // SDL window closed
                    game_running = false;
                    break;

                case SDL_KEYDOWN:

                    // keypress activates the corresponding bit
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_w:
                            player_keys |= UP;
                            break;
                        case SDLK_s:
                            player_keys |= DOWN;
                            break;
                        case SDLK_a:
                            player_keys |= LEFT;
                            break;
                        case SDLK_d:
                            player_keys |= RIGHT;
                            break;
                        default:
                            // nothing
                            break;
                    }

                    break;

                case SDL_KEYUP:

                    // keyrelease deactivates the corresponding bit
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_w:
                            player_keys &= (~UP);
                            break;
                        case SDLK_s:
                            player_keys &= (~DOWN);
                            break;
                        case SDLK_a:
                            player_keys &= (~LEFT);
                            break;
                        case SDLK_d:
                            player_keys &= (~RIGHT);
                            break;
                        default:
                            // nothing
                            break;
                    }

                    break;

                case SDL_WINDOWEVENT_FOCUS_LOST:

                    player_keys = 0U;
                    break;
                
                case SDL_WINDOWEVENT_FOCUS_GAINED:

                    const T_UINT8 * keyState = SDL_GetKeyboardState(nullptr);
                    if (keyState[SDL_SCANCODE_W])
                    {
                        player_keys |= UP;
                    }
                    if (keyState[SDL_SCANCODE_S])
                    {
                        player_keys |= DOWN;
                    }
                    if (keyState[SDL_SCANCODE_A])
                    {
                        player_keys |= LEFT;
                    }
                    if (keyState[SDL_SCANCODE_D])
                    {
                        player_keys |= GameWindow::RIGHT;
                    }
                    
                    break;
            }
        }
    }

    void center_viewport(t_point center)
    {
        view_port->setCenter(center);
    }

    void update_viewport(T_UINT64 dtime, t_point player_position)
    {
        view_port->setPlayerPosition(player_position);
        view_port->update(dtime);
    }

    void set_viewport_mode(t_viewport_mode mode)
    {
        view_port->setMode(mode);
    }
    
    void clear_window()
    {
        SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x00, 0x00, 0x00); // Black background
        SDL_RenderClear(sdl_renderer);
    }
    
    void present_window()
    {
        SDL_RenderPresent(sdl_renderer);
    }

    void destroy()
    {
        if (sdl_renderer) 
        {
            SDL_DestroyRenderer(sdl_renderer);
        }
        if (sdl_window) 
        {
            SDL_DestroyWindow(sdl_window);
        }
        SDL_Quit();
    }

    void *create_texture(t_pixel *pixels, T_UINT16 width, T_UINT16 height)
    {
        SDL_Texture * L_texture = SDL_CreateTexture(sdl_renderer, SDL_PIXELFORMAT_RGB565, SDL_TEXTUREACCESS_STATIC, width, height);

        if (!L_texture)
        {
            SDL_Log("Failed to create texture: %s", SDL_GetError());
        }
        else
        {
            // Update the texture with the pixel data
            SDL_UpdateTexture(L_texture, nullptr, pixels, width * sizeof(T_UINT16));
        }

        // return a pointer to the sdl texture
        return L_texture;
    }
    void *create_texture(Sprite *sprite)
    {
        void * L_texture = nullptr;
        if (sprite)
        {
            // create an sdl surface to help with graphics transformations
            SDL_Surface * L_surface = SDL_CreateRGBSurfaceWithFormatFrom(
                sprite->getSpritePixels(), // pixel data buffer
                sprite->getWidth(), // number of pixels per row
                sprite->getHeight(), // number of pixels per column 
                sizeof(t_pixel) * 8, // number of bits per pixel 
                sprite->getWidth() * sizeof(t_pixel), // number of bytes per row
                SDL_PIXELFORMAT_RGB565 // 5 bits red, 6 green, 5 blue
            );

            if (L_surface)
            {
                // set the color key for transparency
                T_INT32 L_status = SDL_SetColorKey(L_surface, SDL_TRUE, PXCOLOR_TRANSPARENT);
                if (L_status < 0)
                {
                    printf("failed to set transparency pixel\n");
                }

                // create a texture from the surface object
                L_texture = SDL_CreateTextureFromSurface(sdl_renderer, L_surface);
                
                // assign this texture to the sprite 
                sprite->setTexture(L_texture);
                
                // delete the surface object
                SDL_FreeSurface(L_surface);
            }
        }
        else
        {
            printf("failed to create SDL surface\n");
        }
        
        return L_texture;
    }

    void render_texture(void *texture, t_point point, t_vector size)
    {
        if (texture)
        {
            SDL_Rect destRect = { point.x, point.y, size.x, size.y };
            SDL_RenderCopy(sdl_renderer, (SDL_Texture *) texture, nullptr, &destRect);
        }
        else
        {
            printf("tried to render texture from null ptr\n");
        }
    }

    void render_sprite(Sprite *sprite, t_point point, t_vector size)
    {
        if (sprite)
        {
            SDL_Texture * L_texture = (SDL_Texture*) sprite->getTexture();
            render_texture(L_texture, point, size);
        }
        else
        {
            printf("tried to render sprite from null ptr\n");
        }
    }

    void render_sprite_viewport(Sprite * sprite, t_point position, t_vector size)
    {
        if (view_port->intersects(position, size)) 
        {
            t_point render_pos = Vector2::subtract(position, view_port->getPosition());
            render_sprite(sprite, render_pos, size);
        }
    }

    bool is_running()
    {
        return game_running;
    }

    T_UINT16 get_player_keys()
    {
        return player_keys;
    }

    t_vector get_window_size()
    {
        return window_size;
    }
}
