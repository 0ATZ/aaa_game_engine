#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject
{
    public:
        virtual bool init()   = 0;
        virtual void update() = 0;
        virtual void render() = 0;
        virtual void destroy() = 0;
        
    private:
        // int m_x_pos;
        // int m_y_pos;
        
};
#endif