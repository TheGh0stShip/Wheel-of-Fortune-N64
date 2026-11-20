#include "wof.h"
#include "mpeg/proto.h"

/*
=====================
func_800A4CF8

memset
=====================
*/
void *func_800A4CF8( void *s, int c, unsigned int n ) {
    unsigned int i;
    char         *dst;

    dst = s;
    for ( i = 0; i < n; i++ ) {
        dst[i] = c;
    }
    return s;
}
