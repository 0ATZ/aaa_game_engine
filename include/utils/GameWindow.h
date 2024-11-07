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
    T_UINT32 get_player_keys();
    T_UINT32 get_key_presses();
    T_UINT32 get_key_releases();
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
    const T_UINT32 NUM0   = 1U << 0; 
    const T_UINT32 NUM1   = 1U << 1; 
    const T_UINT32 NUM2   = 1U << 2; 
    const T_UINT32 NUM3   = 1U << 3; 
    const T_UINT32 NUM4   = 1U << 4; 
    const T_UINT32 NUM5   = 1U << 5; 
    const T_UINT32 NUM6   = 1U << 6; 
    const T_UINT32 NUM7   = 1U << 7; 
    const T_UINT32 NUM8   = 1U << 8; 
    const T_UINT32 NUM9   = 1U << 9; 
    const T_UINT32 QKEY   = 1U << 10;
    const T_UINT32 WKEY   = 1U << 11;
    const T_UINT32 EKEY   = 1U << 12;
    const T_UINT32 RKEY   = 1U << 13;
    const T_UINT32 AKEY   = 1U << 14;
    const T_UINT32 SKEY   = 1U << 15;
    const T_UINT32 DKEY   = 1U << 16;
    const T_UINT32 FKEY   = 1U << 17;
    const T_UINT32 ZKEY   = 1U << 18;
    const T_UINT32 XKEY   = 1U << 19;
    const T_UINT32 CKEY   = 1U << 20;
    const T_UINT32 VKEY   = 1U << 21;
    // 22 - 26 unimplemented
    const T_UINT32 TAB    = 1U << 27;
    const T_UINT32 SHIFT  = 1U << 28;
    const T_UINT32 SPACE  = 1U << 29;
    const T_UINT32 MOUSE1 = 1U << 30;
    const T_UINT32 MOUSE2 = 1U << 31;

    const T_UINT32 UP     = WKEY;
    const T_UINT32 DOWN   = SKEY;
    const T_UINT32 LEFT   = AKEY;
    const T_UINT32 RIGHT  = DKEY;


    // const T_UINT16 KBD_MASK = 0x15;   // 0000 1111
    // const T_UINT16 MOUSE_MASK = 0x30; // 0011 0000

}

#endif
