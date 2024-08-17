// Header file for input output functions
#include <iostream>
#include <SDL2/SDL.h>
#include "Game.h"

using namespace std;

int WinMain(int argc, char* args[]) {
    Uint32 frameDuration = 1000 / 60; // Frame duration for 60 FPS
    
    Game game;
    if (!game.init()) {
        return 1;
    }
    
    while (game.isRunning())
    {
        Uint32 startTime = SDL_GetTicks();
        game.update();
        game.render();
        Uint32 frameTime = SDL_GetTicks() - startTime;
        if (frameDuration > frameTime) {
            SDL_Delay(frameDuration - frameTime);
        }
    }
    game.destroy();
    return 0;
}