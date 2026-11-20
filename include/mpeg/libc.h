// libc.h -- the player's stand-ins for the C library
//
// The decoder was written for a hosted C library. The player supplies the functions it calls itself, in
// one unit at the end of the module: some work (malloc, fread, memcpy, memset, gettimeofday), the rest
// print "<name>: function not yet implemented" and return. Those messages are where the names of
// fgetc, fseek, realloc, strtok, fopen, sqrt, cos and floor come from. The file name is invented.

#ifndef MPEG_LIBC_H
#define MPEG_LIBC_H

#ifndef NULL
#define NULL 0
#endif

// A stream: the memory the movie sits in, and how far it has been read. There is one, D_80107888.
typedef struct {
    /* 0x00 */ int           unk_00;    // never read or written
    /* 0x04 */ int           pos;
    /* 0x08 */ unsigned char *data;
} FILE;

// The decoder's messages on stderr are compiled out. Where one was the only statement of a block
// ("if ( !quietFlag ) { fprintf( stderr, ... ); }"), retail still makes the test and then does nothing.
// guess: that they went through a macro; a call that was commented out leaves the same code.
#define fprintf( stream, args... )

struct timeval {
    /* 0x00 */ long tv_sec;
    /* 0x04 */ long tv_usec;
};

#endif // MPEG_LIBC_H
