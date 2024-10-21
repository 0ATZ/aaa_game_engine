#ifndef VECTOR2_H
#define VECTOR2_H

#include "GameTypes.h"
#include <math.h>

namespace Vector2
{
    t_point add(t_point p, t_vector v);

    t_point subtract(t_point p, t_vector v);

    t_vector add(t_vector v1, t_vector v2);
    
    t_vector subtract(t_vector v1, t_vector v2);

    t_vector scale(t_vector v, T_FLOAT32 mag);
    
    t_vector invert(t_vector v);

    T_UINT16 magnitude(t_vector v);

    t_vector normalize(t_vector v);
    
}

#endif