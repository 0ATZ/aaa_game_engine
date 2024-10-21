#ifndef VECTOR2_H
#define VECTOR2_H

#include "GameTypes.h"
#include <math.h>

namespace Vector2
{
    typedef struct s_vector
    {
        T_INT32 x;
        T_INT32 y;
    } t_vector;

    t_vector add(t_vector v1, t_vector v2)
    {
        return {v1.x + v2.x, v1.y + v2.y};
    }

    t_vector subtract(t_vector v1, t_vector v2)
    {
        return {v1.x - v2.x, v1.y - v2.y};
    }

    t_vector scale(t_vector v, T_UINT16 mag)
    {
        return {v.x*mag, v.y*mag};
    }

    t_vector invert(t_vector v)
    {
        return {v.x*-1, v.y*-1};
    }

    t_vector normalize(t_vector v)
    {
        T_UINT16 mag = magnitude(v);
        if (mag > 0)
        {
            return { v.x/mag, v.y/mag };
        }
        else
        {
            return {0L, 0L};
        }
    }

    T_UINT16 magnitude(t_vector v)
    {
        return (T_UINT16) sqrt((v.x * v.x) + (v.y * v.y));
    }

}

#endif