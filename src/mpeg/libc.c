// libc.c -- the C library functions the decoder calls, as far as the player has them
//
// The decoder was written for a hosted C library. This unit supplies the functions it still calls:
// fread, memcpy, malloc, memset, fopen, fclose and gettimeofday do something, free does nothing, and
// fgetc, fseek, realloc, exit, strtok, sqrt, cos and floor print that they are missing and return.
// A movie is "opened" by the address it sits at in memory, and there is one stream to open it on.
// The file name is invented; the functions are named by the messages they print and by what they do.

#include "wof.h"
#include "mpeg/proto.h"

// The #ident lines of the system headers this object included, in order: the original assembler put
// the strings into the read-only data, which they open. The headers are not in this tree, so their
// lines stand here.
#ident "$Revision: 1.49 $"
#ident "$Revision: 3.70 $"
#ident "$Revision: 1.5 $"
#ident "$Revision: 1.2 $"
#ident "$Revision: 1.4 $"
#ident "$Revision: 1.17 $"
#ident "$Revision: 1.34 $"
#ident "$Revision: 1.36 $"
#ident "$Revision: 3.97 $"
#ident "$Revision: 1.13 $"
#ident "$Revision: 1.4 $"
#ident "$Revision: 3.31 $"
#ident "$Revision: 1.23 $"

// the stream
FILE D_80107888;

/*
=====================
fread

Copies the next size * nitems bytes of the stream.
=====================
*/
unsigned int fread( void *ptr, unsigned int size, unsigned int nitems, FILE *stream ) {
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
fgetc

Not there: prints that it is missing.
=====================
*/
int fgetc( FILE *stream ) {
    FatalError( "fgetc: function not yet implemented" );
}

/*
=====================
memcpy

Copies n bytes from s2 to s1, a byte at a time.
=====================
*/
void *memcpy( void *s1, const void *s2, unsigned int n ) {
    unsigned int        i;
    char                *dst;
    const unsigned char *src;

    dst = s1;
    src = s2;
    for ( i = 0; i < n; i++ ) {
        dst[i] = src[i];
    }
    return s1;
}

/*
=====================
fseek

Not there: prints that it is missing.
=====================
*/
int fseek( FILE *stream, long offset, int whence ) {
    FatalError( "fseek: function not yet implemented" );
    return 0;
}

/*
=====================
free

Does nothing: what the player allocates stays allocated.
=====================
*/
void free( void *ptr ) {
}

/*
=====================
malloc

Allocates from the heap of the game.
=====================
*/
void *malloc( unsigned int size ) {
    return AllocMem( size );
}

/*
=====================
realloc

Not there: prints that it is missing.
=====================
*/
void *realloc( void *ptr, unsigned int size ) {
    FatalError( "REALLOC: function not yet implemented" );
    return 0;
}

/*
=====================
exit

Prints that the player wanted to exit, and returns to it.
=====================
*/
void exit( int status ) {
    FatalError( "MPEG: exited before done" );
}

/*
=====================
memset

Fills n bytes at s with c, a byte at a time.
=====================
*/
void *memset( void *s, int c, unsigned int n ) {
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
strtok

Not there: prints that it is missing.
=====================
*/
char *strtok( char *s1, char *s2 ) {
    FatalError( "strtok: function not yet implemented" );
    return 0;
}

/*
=====================
fopen

Opens the one stream there is on the movie at `filename`, which is its address in memory.
=====================
*/
FILE *fopen( char *filename ) {
    if ( D_80086D58 != 0 ) {
        FatalError( "fopen: File already open. (MPEG)" );
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

fclose: the stream can be opened again. The name stays a placeholder because game code outside the
player calls the function.
=====================
*/
void func_800A4E58( void *stream ) {
    D_80086D58 = 0;
}

/*
=====================
sqrt

Not there: prints that it is missing.
=====================
*/
double sqrt( double x ) {
    FatalError( "sqrt: function not yet implemented" );
    return 0.0;
}

/*
=====================
cos

Not there: prints that it is missing.
=====================
*/
double cos( double x ) {
    FatalError( "cos: function not yet implemented" );
    return 0.0;
}

/*
=====================
floor

Not there: prints that it is missing.
=====================
*/
double floor( double x ) {
    FatalError( "floor: function not yet implemented" );
    return 0.0;
}

/*
=====================
gettimeofday

The time since the console was switched on.

BUG: the tick count goes through a long, so the time is that of the low 32 bits of the count: it
starts again from zero, by way of the negative numbers, every 2 to the 32nd ticks.
=====================
*/
int gettimeofday( struct timeval *tp, ... ) {
    long ticks;

    ticks = osGetTime();
    tp->tv_sec = ticks / osClockRate;
    ticks = ticks % osClockRate;
    tp->tv_usec = ( (s64)ticks * 1000000 ) / osClockRate;
    return 0;
}
