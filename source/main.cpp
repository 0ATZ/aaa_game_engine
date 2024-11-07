// Header file for input output functions
#include <iostream>
#include <SDL2/SDL.h>
#include "BaseTypes.h"
#include "Game.h"

/* Uncomment this line for unreasonably low performance! */
#define LOW_PERFORMANCE_MODE

using namespace std;

int WinMain(void) {
    
    Game game;
    if (!game.init()) {
        return 1;
    }
    const T_UINT64 FRAME_DURATION_60FPS = 1000 / 60; // Frame duration for 60 FPS
    // const T_UINT64 FRAME_DURATION_120FPS = 1000 / 120; // Frame duration for 120 FPS
    // const T_UINT64 FRAME_DURATION_140FPS = 1000 / 140; // Frame duration for 140 FPS

    // This variable controls the speed that the game world updates
    const T_UINT64 UPDATE_DURATION_MS = FRAME_DURATION_60FPS;

    // Adjust this variable to change the frame rate
    const T_UINT64 RENDER_DURATION_MS = FRAME_DURATION_60FPS;

    // TODO: use high resolution nanosecond clock
    // keep track of the last update and render time
    const T_UINT64 gameStart = SDL_GetTicks64();
    T_UINT64 prevUpdate = gameStart;
    T_UINT64 prevRender = gameStart;
    while (game.isRunning())
    {
        // perform the game update seperately to keep it consistent
        T_UINT64 dtime = (SDL_GetTicks64() - prevUpdate);
        if (dtime >= UPDATE_DURATION_MS)
        {
            prevUpdate = SDL_GetTicks64();
            game.update(dtime);
        }

        // perform the screen render separately to adjust frame rate
        if ((SDL_GetTicks64() - prevRender) >= RENDER_DURATION_MS)
        {
            prevRender = SDL_GetTicks64();

            game.render();
        }
#ifdef LOW_PERFORMANCE_MODE
        // delay makes timing inaccurate due to CPU scheduling overhead
        // however, delay also significantly decreases CPU usage 
        SDL_Delay(1);
#endif
    }
    game.destroy();
    return 0;
}