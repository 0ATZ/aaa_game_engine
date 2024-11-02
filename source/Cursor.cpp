#include "Cursor.h"
#include "AnimatedSprite.h"
#include "GameWindow.h"

Cursor::Cursor()
{
    m_clicked = false;
    m_timer = 0ULL;
    m_position = {300, 300};
    m_sizePx = {48, 48};
    m_solid = false;
    m_sprite = new AnimatedSprite("./assets/sprites/cursors.bin", 4, 16, 16, 1);
}

void Cursor::update(T_UINT64 dtime)
{
    m_timer += dtime; 
    if (m_timer > 2000ULL)
    {
        m_timer = 0ULL;
        ((AnimatedSprite*)m_sprite)->advanceFrame();
    } 
}

void Cursor::render()
{
    // Adjust the position and size of cursor for hitbox
    GameWindow::render_sprite_viewport(m_sprite, m_position, m_sizePx);
}

void Cursor::destroy()
{
    delete this;
}

void Cursor::vResolveCollision(PhysicsObject *obj)
{
    // TODO: resolve collision for clicks
}
