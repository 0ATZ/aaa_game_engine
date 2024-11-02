#include "Cursor.h"
#include "AnimatedSprite.h"
#include "GameWindow.h"
#include "Vector2.h"
#include <stdio.h>

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
    
    // offset the mouse position by the position of the camera
    // to get the "ingame" position of the cursor object
    t_point cursorPosition = Vector2::add(
        GameWindow::get_mouse_position(), 
        GameWindow::get_viewport_position()
    );
    setPosition(cursorPosition);
    
    // get the key states from GameWindow
    T_UINT16 playerKeys = GameWindow::get_player_keys();
    if (playerKeys & GameWindow::MOUSE1)
    {
        // set the sprite to the "clicked" cursor
        ((AnimatedSprite*)m_sprite)->setCurrentFrame(3);
    }
    else
    {
        // set the sprite to the "not clicked" cursor
        ((AnimatedSprite*)m_sprite)->setCurrentFrame(2);
    }
}

void Cursor::render()
{
    // Adjust the position and size of cursor for hitbox
    t_point cursorPosition = Vector2::subtract(m_position, Vector2::scale(m_sizePx, 0.5));
    GameWindow::render_sprite_viewport(m_sprite, cursorPosition, m_sizePx);
}

void Cursor::destroy()
{
    delete this;
}

void Cursor::vResolveCollision(PhysicsObject *obj)
{
    // TODO: resolve collision for clicks
}
