#include "wof.h"
#include "mpeg/proto.h"
#include "mpeg/util.h"

/*
=====================
func_800890C8

Reads the extra information of a picture or slice header: bytes that each follow a set flag bit, up
to the first clear one. Returns a buffer it allocates, or NULL when the first flag is clear.
=====================
*/
char *func_800890C8( VidStream *vid_stream ) {
    unsigned int size, marker;
    char         *dataPtr;
    unsigned int data;

    get_bits1( data );

    if ( !data ) {
        return NULL;
    }

    size = EXT_BUF_SIZE;
    dataPtr = (char *)func_800A4C28( size );
    marker = 0;

    while ( data ) {
        get_bits8( data );

        dataPtr[marker] = (char)data;
        marker++;

        if ( marker == size ) {
            size += EXT_BUF_SIZE;
            dataPtr = (char *)func_800A4C70( dataPtr, size );
        }

        get_bits1( data );
    }

    // give back what was not used
    dataPtr = (char *)func_800A4C70( dataPtr, marker );

    return dataPtr;
}
