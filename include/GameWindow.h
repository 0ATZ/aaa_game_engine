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
    const T_UINT16 UP     = 0x01U; // 0000 0001
    const T_UINT16 DOWN   = 0x02U; // 0000 0010
    const T_UINT16 LEFT   = 0x04U; // 0000 0100
    const T_UINT16 RIGHT  = 0x08U; // 0000 1000
    const T_UINT16 MOUSE1 = 0x10U; // 0001 0000
    const T_UINT16 MOUSE2 = 0x20U; // 0010 0000
    const T_UINT16 KBD_MASK = 0x15;   // 0000 1111
    const T_UINT16 MOUSE_MASK = 0x30; // 0011 0000

}

#endif
