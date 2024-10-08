#include "KeyListener.h"
#include <iostream>

KeyListener::KeyListener()
{
    // Initialize the key states for WASD to false
    keyStates[SDLK_w] = false;
    keyStates[SDLK_a] = false;
    keyStates[SDLK_s] = false;
    keyStates[SDLK_d] = false;
}

KeyListener::~KeyListener() {}

void KeyListener::update(SDL_Event& event)
{
    // Update the state of keys when an event is detected
    if (event.type == SDL_KEYDOWN) 
    {
        std::cout << "key pressed: " << event.key.keysym.sym << std::endl;
        keyStates[event.key.keysym.sym] = true;
    } 
    else if (event.type == SDL_KEYUP) 
    {
        keyStates[event.key.keysym.sym] = false;
    }
}

bool KeyListener::isKeyPressed(SDL_Keycode key) 
{
    if (keyStates.find(key) != keyStates.end()) 
    {
        return keyStates[key];
    }
    return false;
}
