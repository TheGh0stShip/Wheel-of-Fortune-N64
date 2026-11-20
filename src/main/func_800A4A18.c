#include "wof.h"
#include "mpeg/proto.h"

/*
=====================
func_800A4A18

fread: copies the next size * nitems bytes of the stream.
=====================
*/
unsigned int func_800A4A18( void *ptr, unsigned int size, unsigned int nitems, FILE *stream ) {
    int  i;
    int  total;
    char *dst;

    dst = ptr;
    total = nitems * size;
    for ( i = 0; i < total; i++ ) {
        dst[i] = stream->data[stream->pos++];
    }
    return nitems;
}
