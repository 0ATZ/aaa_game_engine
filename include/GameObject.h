#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Sprite.h"

class GameObject
{
    public:
        virtual bool init()   = 0;
        virtual void update() = 0;
        virtual void render() = 0;
        virtual void destroy() = 0;

        // TODO: move this to a PhysicsObject cpp file
        void setPosition(t_point position) {
            m_position = position;
        }
        t_point getPosition() {
            return m_position;
        }
        void setCenterPosition(t_point position) {
            m_position.x = position.x - m_sizePixels.x/2;
            m_position.y = position.y - m_sizePixels.y/2;
        }
        t_point getCenterPosition() {
            t_point L_center = {
                m_position.x + m_sizePixels.x/2,
                m_position.y + m_sizePixels.y/2,
            };
            return L_center;
        }
        t_point getSizePixels() {return m_sizePixels;}
        void movePosition(t_point mover) {
            m_position.x += mover.x;
            m_position.y += mover.y;
        }
        t_point invertPosition()
        {
            t_point L_inverted = {
                m_position.x * -1,
                m_position.y * -1
            };
            return L_inverted;
        }

    protected:
        t_point m_position;
        t_point m_sizePixels;  // TODO: how to calc collisions
        t_point m_direction;
        T_UINT16 m_speedPx;
        Sprite * m_defaultSprite;
};
#endif