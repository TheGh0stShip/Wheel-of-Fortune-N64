#include "wof.h"
#include "mpeg/proto.h"

/*
=====================
func_800A4F74

gettimeofday: the time since the console was switched on.
=====================
*/
int func_800A4F74( struct timeval *tp, ... ) {
    long ticks;

    ticks = osGetTime();
    tp->tv_sec = ticks / D_80084218;
    ticks = ticks % D_80084218;
    tp->tv_usec = ( (s64)ticks * 1000000 ) / D_80084218;
    return 0;
}
