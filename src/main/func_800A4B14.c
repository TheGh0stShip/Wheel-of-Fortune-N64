#include "wof.h"
#include "mpeg/proto.h"

/*
=====================
func_800A4B14

memcpy
=====================
*/
void *func_800A4B14( void *s1, void *s2, unsigned int n ) {
    unsigned int  i;
    char          *dst;
    unsigned char *src;

    dst = s1;
    src = s2;
    for ( i = 0; i < n; i++ ) {
        dst[i] = src[i];
    }
    return s1;
}
