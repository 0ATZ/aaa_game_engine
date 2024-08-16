// Header file for input output functions
#include <iostream>
#include "Game.h"

using namespace std;

int WinMain(int argc, char* args[]) {
    Game game;
    if (!game.init()) {
        return 1;
    }
    game.run();
    game.cleanUp();
    return 0;
}