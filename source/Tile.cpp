#include "Tile.h"

Tile::Tile(t_tile *tilePixels) :
   Sprite((t_pixel *) tilePixels, TILE_WIDTH, TILE_HEIGHT)
{
    // do nothing, pass parameters to base constructor 
}