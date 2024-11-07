#ifndef BUFFERIO_H
#define BUFFERIO_H

#include "GameTypes.h"

namespace BufferIO
{

    T_UINT16 writeBuffer(const char * const filename, const void * const buffer, 
        const T_UINT16 objectSize, const T_UINT16 objectCount);

    T_UINT16 readBuffer(const char * const filename, void * const buffer, 
        const T_UINT16 objectSize, const T_UINT16 objectCount);

    T_UINT16 readRect_RGB565(const char * const filename, t_pixel * const buffer,
        const T_UINT16 width, const T_UINT16 height);
    
    T_UINT16 writeRect_RGB565(const char * const filename, const t_pixel * const buffer, 
        const T_UINT16 width, const T_UINT16 height);

}

#endif
