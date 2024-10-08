#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Window.h"
#include "GameObject.h"

class Rectangle: public GameObject
{
    public:
        Rectangle(Window * window, int pixelWidth, int pixelHeight);
        bool init();
        void update();
        void render();
        void destroy();
        
    private:
        int m_pixelWidth;
        int m_pixelHeight;
        int m_x_pos;
        int m_y_pos;
        Window * m_window;
};
#endif
