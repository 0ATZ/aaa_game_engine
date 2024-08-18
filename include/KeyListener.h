#ifndef KEYLISTENER_H
#define KEYLISTENER_H

#include <SDL2/SDL.h>
#include <unordered_map>

class KeyListener : public GameObject
{
    public:
        KeyListener();
        ~KeyListener();
        
        // Update the state of keys
        void update(SDL_Event& event);

        // Check if a key is currently pressed
        bool isKeyPressed(SDL_Keycode key);
        
    private:
        std::unordered_map<SDL_Keycode, bool> keyStates;
};

#endif