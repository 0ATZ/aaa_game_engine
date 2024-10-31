#ifndef WINDOW_H
#define WINDOW_H

#include "BaseTypes.h"
#include "SDL2/SDL.h"
#include "Sprite.h"
#include "GameObject.h"



namespace GameWindow
{
    bool initialize(t_vector window_size);
    void process_events();
    void clear_window();
    void present_window();
    void destroy();

    //TODO: abstract the texture pointer
    // typedef SDL_Texture t_texture
    void * create_texture(t_pixel * pixels, T_UINT16 width, T_UINT16 height);
    void * create_texture(Sprite * sprite);
    void render_texture(void *texture, t_point point, t_vector size);
    void render_sprite(Sprite *sprite, t_point point, t_vector size);
    void render_sprite_viewport(Sprite * sprite, t_point position, t_vector size);

    bool is_running();
    T_UINT16 get_player_keys();
    t_vector get_window_size();
    void center_viewport(t_point center);
    void update_viewport(T_UINT64 dtime, t_point player_position);
    void set_viewport_mode(t_viewport_mode mode);

    // player key codes
    const T_UINT16 UP    = 0x01U; // 0001
    const T_UINT16 DOWN  = 0x02U; // 0010
    const T_UINT16 LEFT  = 0x04U; // 0100
    const T_UINT16 RIGHT = 0x08U; // 1000

}

#endif
