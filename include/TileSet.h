#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include "BaseTypes.h"
#include "GameTypes.h"
#include "SDL2/SDL.h"


// TODO: implement delete tile? 
class TileSet
{
    public:
        TileSet(SDL_Renderer *renderer);
        TileSet(SDL_Renderer *renderer, t_tileset tileSet);

        bool hasSpace();
        t_index addTile(t_tile *tile);
        SDL_Texture * getTexture(t_index textureID);
        
    private:
        static const T_UINT16 TEXTURE_CACHE_SIZE = TILESET_SIZE;
        typedef SDL_Texture* t_texture_cache[TEXTURE_CACHE_SIZE];

        T_UINT16 m_tileCount;  // number of tiles in tileset
        SDL_Renderer * m_renderer; // SDL uses renderer to create the textures
        t_texture_cache m_textureCache;  // store pointers to SDL textures for each tile
};


#endif