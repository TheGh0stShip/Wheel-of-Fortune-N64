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
    /* 0x00 */ int           unused00;  // NOTE: no code reads or writes it
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

// libc.c. fclose is declared in wof.h, because game code calls it.
unsigned int fread( void *ptr, unsigned int size, unsigned int nitems, FILE *stream );
int fgetc( FILE *stream );
void *memcpy( void *s1, const void *s2, unsigned int n );
int fseek( FILE *stream, long offset, int whence );
void free( void *ptr );
void *malloc( unsigned int size );
void *realloc( void *ptr, unsigned int size );
void exit( int status );
void *memset( void *s, int c, unsigned int n );
char *strtok( char *s1, char *s2 );
FILE *fopen( char *filename );
double sqrt( double x );
double cos( double x );
double floor( double x );
int gettimeofday( struct timeval *tp, ... );

extern FILE D_80107888;

#endif // MPEG_LIBC_H
