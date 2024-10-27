#include "BufferIO.h"
#include <cstdio>

namespace BufferIO
{

    // returns bytes written
    T_UINT16 writeBuffer(const char * const filename, const void * const buffer, 
        const T_UINT16 objectSize, const T_UINT16 objectCount)
    {

        if (!filename || !buffer)
        {
            printf("writeBuffer: invalid parameter, null pointer detected\n");
            return 0ULL;
        }

        if (objectSize == 0ULL || objectCount == 0ULL)
        {
            printf("successfully wrote nothing.\n");
            return 0ULL;
        }

        FILE * fp =  nullptr;
        // open the file in binary write mode
        fp = fopen(filename, "wb"); 
        if (!fp)
        {
            printf("failed to open file: %s\n", filename);
            return 0ULL;
        }

        // write buffer to the file
        T_UINT16 objectsWritten = fwrite(buffer, objectSize, objectCount, fp);
        if (objectsWritten == 0ULL)
        {
            printf("failed to write file: %s\n", filename);
        }

        fclose(fp);

        T_UINT16 bytesWritten = (objectsWritten * objectSize);
        return bytesWritten;
    }

    T_UINT16 readBuffer(const char * const filename, void * const buffer, 
        const T_UINT16 objectSize, const T_UINT16 objectCount)
    {
        if (!filename || !buffer)
        {
            printf("readBuffer: invalid parameter, null pointer detected\n");
            return 0ULL;
        }

        if (objectSize == 0ULL || objectCount == 0ULL)
        {
            printf("successfully read nothing.\n");
            return 0ULL;
        }

        FILE * fp =  nullptr;
        // open the file in binary write mode
        fp = fopen(filename, "rb"); 
        if (!fp)
        {
            printf("failed to open file: %s\n", filename);
            return 0ULL;
        }

        T_UINT16 objectsRead = fread(buffer, objectSize, objectCount, fp);
        if (objectsRead == 0ULL)
        {
            printf("failed to read file: %s\n", filename);
        }

        fclose(fp);

        T_UINT16 bytesRead = (objectsRead * objectSize);
        printf("read bytes: %d\n", bytesRead);
        return bytesRead;
    }

    // writes raw pixels to a binary file
    T_UINT16 writeRect_RGB565(const char * const filename, const t_pixel * const buffer, 
        const T_UINT16 width, const T_UINT16 height)
    {
        // write the whole buffer and return the number of bytes written
        return writeBuffer(filename, buffer, (width * height * sizeof(t_pixel)), 1ULL);
    }

    // read raw pixels from a binary file
    T_UINT16 readRect_RGB565(const char * const filename, t_pixel * const buffer,
        const T_UINT16 width, const T_UINT16 height)
    {
        // read a full buffer from the file
        return readBuffer(filename, buffer, (width * height * sizeof(t_pixel)), 1ULL);
    }

}