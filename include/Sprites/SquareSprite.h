#ifndef SQUARE_SPRITE_H
#define SQUARE_SPRITE_H

#include "BaseTypes.h"
#include "GameTypes.h"

const t_pixel BLACK = 0x0000U;
const t_pixel WHITE = 0xFFFFU;
const t_pixel RED   = 0xF800U;
const t_pixel GREEN = 0x07E0U;
const t_pixel BLUE  = 0x001FU;

t_tile TILE_BLACK = {BLACK}; // I dont think this works right... probably only sets one byte at a time
t_tile TILE_GREEN = {GREEN}; // I dont think this works right... probably only sets one byte at a time

#endif