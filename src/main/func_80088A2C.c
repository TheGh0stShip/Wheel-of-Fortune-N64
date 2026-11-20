#include "wof.h"
#include "mpeg/proto.h"
#include "mpeg/util.h"

/*
=====================
func_80088A2C

Reads extension or user data, the bytes up to the next start code, into a buffer it allocates.
=====================
*/
char *func_80088A2C( VidStream *vid_stream ) {
    unsigned int size, marker;
    char         *dataPtr;
    unsigned int data;

    size = EXT_BUF_SIZE;
    dataPtr = (char *)func_800A4C28( size );
    marker = 0;

    while ( !func_800888C0( 24, 0x000001, vid_stream ) ) {
        get_bits8( data );

        dataPtr[marker] = (char)data;
        marker++;

        if ( marker == size ) {
            size += EXT_BUF_SIZE;
            dataPtr = (char *)func_800A4C70( dataPtr, size );
        }
    }

    // give back what was not used
    dataPtr = (char *)func_800A4C70( dataPtr, marker );

    return dataPtr;
}
