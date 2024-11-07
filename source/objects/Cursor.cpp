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
    m_sizePx = {5, 5};
    // m_sprite = new Sprite("./assets/sprites/red_16x16.bin", 16,16);

    // GameWindow handles rendering of cursor 
    SpriteSheet sprites = SpriteSheet("./assets/sprites/cursors.bin", 3, 32, 32);
    GameWindow::create_custom_cursors(&sprites);
}

bool Cursor::init()
{
    return true;
}

void Cursor::update(T_UINT64 dtime)
{
    // offset the mouse position by the position of the camera
    // to get the "ingame" position of the cursor object
    setCenter(GameWindow::get_ingame_mouse_position());
    
    // get the key states from GameWindow
    T_UINT32 playerKeys = GameWindow::get_player_keys();
    if (playerKeys & GameWindow::MOUSE1)
    {
        m_clicked = true;
        if (m_timer < 50)
        {
            // set the cursor to the "clicked" state
            // use this frame as a cool intermediate animation
            GameWindow::set_cursor(1);
            m_timer += dtime;
        }
        else
        {
            // set the cursor to the "held clicked" state
            GameWindow::set_cursor(2);
        }
    }
    else
    {
        // set the cursor to the "unclicked" state
        GameWindow::set_cursor(0);
        m_timer = 0ULL;
        m_clicked = false;
    }
}

bool Cursor::processClick(GameObject *obj)
{
    bool L_clicked = false;
    if (m_clicked && obj)
    {
        L_clicked = intersects(obj->getPosition(), obj->getSizePixels());
        if (L_clicked)
        {
            obj->vOnClick();
        }
    }
    return L_clicked;
}

void Cursor::vOnClick()
{
    // do nothing
}

void Cursor::render()
{
    // Cursor render is not called in the main game loop
    // GameWindow::render_sprite_viewport(m_sprite, m_position, {8,8});
}

void Cursor::destroy()
{
    delete this;
}

bool Cursor::isClicked()
{
    return m_clicked;
}
