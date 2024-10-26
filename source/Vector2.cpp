#include "Vector2.h"

namespace Vector2
{
    t_vector add(t_vector v1, t_vector v2)
    {
        return {v1.x + v2.x, v1.y + v2.y};
    }

    t_vector subtract(t_vector v1, t_vector v2)
    {
        return {v1.x - v2.x, v1.y - v2.y};
    }

    t_vector multiply(t_vector v1, t_vector v2)
    {
        return {v1.x * v2.x, v1.y * v2.y};
    }

    t_vector scale(t_vector v, T_FLOAT32 mag)
    {
        return { (T_INT32)(v.x * mag), (T_INT32)(v.y * mag) };
    }

    t_vector invert(t_vector v)
    {
        return {v.x*-1, v.y*-1};
    }

    T_UINT16 magnitude(t_vector v)
    {
        return (T_UINT16) sqrt((v.x * v.x) + (v.y * v.y));
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

}