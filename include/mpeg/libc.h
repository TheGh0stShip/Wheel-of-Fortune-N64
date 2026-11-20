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

#define EOF ( -1 )

// network byte order is the byte order of the machine
#define ntohl( x ) ( x )
#define htonl( x ) ( x )

// assert.h, as NDEBUG leaves it
#define assert( expression ) ( (void)0 )

struct timeval {
    /* 0x00 */ long tv_sec;
    /* 0x04 */ long tv_usec;
};

// libc.c. fclose is func_800A4E58, declared in wof.h.
unsigned int func_800A4A18( void *ptr, unsigned int size, unsigned int nitems, FILE *stream );
int func_800A4AD8( FILE *stream );
void *func_800A4B14( void *s1, void *s2, unsigned int n );
int func_800A4BB4( FILE *stream, long offset, int whence );
void func_800A4C04( void *ptr );
void *func_800A4C28( unsigned int size );
void *func_800A4C70( void *ptr, unsigned int size );
void func_800A4CBC( int status );
void *func_800A4CF8( void *s, int c, unsigned int n );
char *func_800A4D84( char *s1, char *s2 );
FILE *func_800A4DD0( char *filename );
double func_800A4E84( double x );
double cos( double x );
double func_800A4F24( double x );
int func_800A4F74( struct timeval *tp, ... );

extern FILE D_80107888;

#endif // MPEG_LIBC_H
