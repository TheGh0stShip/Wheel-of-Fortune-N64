#include "wof.h"
#include "mpeg/proto.h"

/*
=====================
func_80089490

The time in seconds.
=====================
*/
double func_80089490( void ) {
    struct timeval tv;

    (void)func_800A4F74( &tv, NULL );
    return ( tv.tv_sec + tv.tv_usec / 1000000.0 );
}
