#ifndef GAMETYPES_H
#define GAMETYPES_H

#include "BaseTypes.h"

// TODO: update code to use this instead of separate x and y variables
// point describes an (x,y) coordinate in a 2D plane
typedef struct s_point
{
    T_INT32 x;
    T_INT32 y;
} t_point;

// 16-bit pixels (RGB565)
typedef T_UINT16 t_pixel;

typedef enum e_scale 
{
    SCALE_ORIGINAL = 1U,
    SCALE_DOUBLE   = 2U,
    SCALE_TRIPLE   = 3U,
    SCALE_QUADRA   = 4U,
} t_scale;

// tile is a 16X16 square of pixels
const T_UINT16 TILE_WIDTH  = 16U;
const T_UINT16 TILE_HEIGHT = 16U;
const T_UINT16 TILE_SIZE = TILE_WIDTH * TILE_HEIGHT;
typedef T_UINT16 t_tile[TILE_SIZE];

// index represents a value [0..255]
// this value indicates a tile from t_tileset 
typedef T_UINT8 t_index;

// tileset is a list of pointers to 256 tiles
// 256 tile limit allows for 8-bit indexing 
// range of uint8 is [0..255]
const T_UINT16 TILESET_SIZE = 256U;
typedef t_tile* t_tileset[TILESET_SIZE];

// tilemap represents the pixels to be rendered on the screen  
// each tile in the tilemap is represented by an index (8-bit unsigned integer)
// tilemap represents a (TILE_SIZE x TILEMAP_WIDTH x TILEMAP_HEIGHT) pixel square
const T_UINT16 TILEMAP_WIDTH = 16U;
const T_UINT16 TILEMAP_HEIGHT = 16U;
const T_UINT16 TILEMAP_SIZE = TILEMAP_WIDTH * TILEMAP_HEIGHT;
typedef t_index t_tilemap[TILEMAP_SIZE];

#endif