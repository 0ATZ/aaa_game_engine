#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "GameWindow.h"
#include "GameObject.h"
#include "Tile.h"

class Rectangle: public GameObject
{
    public:
        Rectangle(GameWindow * window, int pixelWidth, int pixelHeight);
        bool init();
        void update();
        void render();
        void destroy();
        
    private:
        GameWindow * m_window;
};
#endif
