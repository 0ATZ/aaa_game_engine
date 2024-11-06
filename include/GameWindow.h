#ifndef WINDOW_H
#define WINDOW_H

#include "BaseTypes.h"
#include "SDL2/SDL.h"
#include "Sprite.h"
#include "GameObject.h"
#include "SpriteSheet.h"


namespace GameWindow
{
    bool initialize(t_vector window_size);
    void process_events();
    void clear_window();
    void present_window();
    void destroy();

    //TODO: abstract the texture pointer
    // typedef SDL_Texture t_texture
    // void * create_texture(t_pixel * pixels, T_UINT16 width, T_UINT16 height);
    void * create_texture(Sprite * sprite);
    void render_texture(void *texture, t_point point, t_vector size);
    void render_sprite(Sprite *sprite, t_point point, t_vector size);
    void render_sprite_viewport(Sprite * sprite, t_point position, t_vector size);
    void create_custom_cursors(SpriteSheet * sprites);
    void set_cursor(T_UINT16 index);


    bool is_running();
    T_UINT16 get_player_keys();
    T_UINT16 get_key_presses();
    T_UINT16 get_key_releases();
    t_vector get_window_size();
    t_point get_mouse_position();
    t_point get_ingame_mouse_position();
    t_point get_viewport_position();
    t_point get_game_obj_position(t_point relative_position);
    t_point get_relative_position(t_point game_obj_position);
    void center_viewport(t_point center);
    void update_viewport(T_UINT64 dtime, t_point player_position);
    void set_viewport_mode(t_viewport_mode mode);

    // player key codes
    const T_UINT16 UP     = 1U << 0;  // 0000 0000 0000 0001
    const T_UINT16 DOWN   = 1U << 1;  // 0000 0000 0000 0010
    const T_UINT16 LEFT   = 1U << 2;  // 0000 0000 0000 0100
    const T_UINT16 RIGHT  = 1U << 3;  // 0000 0000 0000 1000
    const T_UINT16 NUM0   = 1U << 4;  // 0000 0000 0001 0000
    const T_UINT16 NUM1   = 1U << 5;  // 0000 0000 0010 0000
    const T_UINT16 NUM2   = 1U << 6;  // 0000 0000 0100 0000
    const T_UINT16 NUM3   = 1U << 7;  // 0000 0000 1000 0000
    const T_UINT16 NUM4   = 1U << 8;  // 0000 0001 0000 0000
    const T_UINT16 NUM5   = 1U << 9;  // 0000 0010 0000 0000
    const T_UINT16 NUM6   = 1U << 10; // 0000 0100 0000 0000
    const T_UINT16 NUM7   = 1U << 11; // 0000 1000 0000 0000
    const T_UINT16 NUM8   = 1U << 12; // 0001 0000 0000 0000
    const T_UINT16 NUM9   = 1U << 13; // 0010 0000 0000 0000
    const T_UINT16 MOUSE1 = 1U << 14; // 0100 0000 0000 0000
    const T_UINT16 MOUSE2 = 1U << 15; // 1000 0000 0000 0000

    // const T_UINT16 KBD_MASK = 0x15;   // 0000 1111
    // const T_UINT16 MOUSE_MASK = 0x30; // 0011 0000

}

#endif
