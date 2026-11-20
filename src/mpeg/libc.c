// libc.c -- the C library functions the decoder calls, as far as the player has them
//
// The decoder was written for a hosted C library. This unit supplies the functions it still calls:
// fread, memcpy, malloc, memset, fopen, fclose and gettimeofday do something, free does nothing, and
// fgetc, fseek, realloc, exit, strtok, sqrt, cos and floor print that they are missing and return.
// A movie is "opened" by the address it sits at in memory, and there is one stream to open it on.
// The file name is invented; the functions are named by the messages they print and by what they do.

#include "wof.h"
#include "mpeg/proto.h"

// the stream
FILE D_80107888;

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

/*
=====================
func_800A4AD8

fgetc: not there.
=====================
*/
int func_800A4AD8( FILE *stream ) {
    func_80009F38( "fgetc: function not yet implemented" );
}

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

/*
=====================
func_800A4BB4

fseek: not there.
=====================
*/
int func_800A4BB4( FILE *stream, long offset, int whence ) {
    func_80009F38( "fseek: function not yet implemented" );
    return 0;
}

/*
=====================
func_800A4C04

free: does nothing. What the player allocates stays allocated.
=====================
*/
void func_800A4C04( void *ptr ) {
}

/*
=====================
func_800A4C28

malloc: the game's allocator.
=====================
*/
void *func_800A4C28( unsigned int size ) {
    return func_8000B924( size );
}

/*
=====================
func_800A4C70

realloc: not there.
=====================
*/
void *func_800A4C70( void *ptr, unsigned int size ) {
    func_80009F38( "REALLOC: function not yet implemented" );
    return 0;
}

/*
=====================
func_800A4CBC

exit: reports it and returns to the caller.
=====================
*/
void func_800A4CBC( int status ) {
    func_80009F38( "MPEG: exited before done" );
}

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

/*
=====================
func_800A4D84

strtok: not there.
=====================
*/
char *func_800A4D84( char *s1, char *s2 ) {
    func_80009F38( "strtok: function not yet implemented" );
    return 0;
}

/*
=====================
func_800A4DD0

fopen: opens the one stream there is on the movie at `filename`, which is its address in memory.
=====================
*/
FILE *func_800A4DD0( char *filename ) {
    if ( D_80086D58 != 0 ) {
        func_80009F38( "fopen: File already open. (MPEG)" );
        return 0;
    }
    D_80086D58 = 1;
    D_80107888.data = filename;
    D_80107888.pos = 0;
    return &D_80107888;
}

/*
=====================
func_800A4E58

fclose
=====================
*/
void func_800A4E58( void *stream ) {
    D_80086D58 = 0;
}

/*
=====================
func_800A4E84

sqrt: not there.
=====================
*/
double func_800A4E84( double x ) {
    func_80009F38( "sqrt: function not yet implemented" );
    return 0.0;
}

/*
=====================
cos

cos: not there.
=====================
*/
double cos( double x ) {
    func_80009F38( "cos: function not yet implemented" );
    return 0.0;
}

/*
=====================
func_800A4F24

floor: not there.
=====================
*/
double func_800A4F24( double x ) {
    func_80009F38( "floor: function not yet implemented" );
    return 0.0;
}

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
