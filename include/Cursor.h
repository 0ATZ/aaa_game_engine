#ifndef CURSOR_H
#define CURSOR_H

#include "GameTypes.h"
#include "PhysicsObject.h"

class Cursor : public GameObject
{
    public:
        Cursor();
        
        bool init();
        void update(T_UINT64 dtime);
        void render();
        void destroy();
        bool isClicked();
        bool processClick(GameObject * obj);
        void vOnClick();

    private: 
        bool m_clicked;
        T_UINT64 m_timer;

};


#endif
