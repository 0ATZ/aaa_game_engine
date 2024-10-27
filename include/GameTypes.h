#ifndef GAMETYPES_H
#define GAMETYPES_H

#include "BaseTypes.h"


typedef struct s_vector
{
    T_INT32 x;
    T_INT32 y;
} t_vector;

// point describes an (x,y) coordinate in a 2D plane
typedef t_vector t_point; 

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
const T_UINT16 MAX_TILEMAP_WIDTH = 64U;
const T_UINT16 MAX_TILEMAP_HEIGHT = 64U;
const T_UINT16 MAX_TILEMAP_SIZE = MAX_TILEMAP_WIDTH * MAX_TILEMAP_HEIGHT;
typedef t_index t_tilemap[MAX_TILEMAP_SIZE];

#endif