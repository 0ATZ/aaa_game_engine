#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <iostream>

class Game {
    public:
        Game();
        bool init();
        void run();
        void cleanUp();
        void renderRectangle(int x, int y);

    private:
        int x_pos = 0;
        int y_pos = 0;
        SDL_Window* window;
        SDL_Renderer* renderer;
        bool running;
        Uint32 lastFrameTime;
        void handleEvents();
        void update();
        void render();
};

#endif // GAME_H