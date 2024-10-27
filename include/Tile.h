#ifndef TILE_H
#define TILE_H

#include "GameTypes.h"
#include "Sprite.h"

// tile is a square shaped sprite 
class Tile : public Sprite
{
    public:
        Tile(t_tile *tilePixels);
        Tile(const char *const filename);
};

#endif