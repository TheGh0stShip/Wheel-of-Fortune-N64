// proto.h -- the MPEG player's functions and globals
//
// Three of the module's functions are declared in wof.h instead, because game code outside the player
// calls them: func_8009CEC0, func_8009D244 and func_800A4E58, and with them the flag D_80086D58.

#ifndef MPEG_PROTO_H
#define MPEG_PROTO_H

#include "mpeg/video.h"

// util.c
void func_800887D8( VidStream *vid_stream );
int func_800888C0( int num, unsigned int mask, VidStream *vid_stream );
char *func_80088A2C( VidStream *vid_stream );
int func_80088C58( VidStream *vid_stream );
char *func_800890C8( VidStream *vid_stream );

// The message of func_800887D8, "Unexpected read error.". It is the last thing in its object's
// read-only data, and retail's fill behind it is not zero (stale bytes of the assembler's buffer), so
// the gate cannot place a literal there: it compares the literal's own padding with that fill.
extern char D_800879DC[];

// video.c
double func_80089490( void );
void func_800894F8( void );
VidStream *func_800895C4( unsigned int buffer_len );
void func_80089898( VidStream *vid );
PictImage *func_80089984( VidStream *vid_stream, XInfo *xinfo );


// libc.c
void func_800A4C04( void *ptr );
void *func_800A4C28( unsigned int size );
void *func_800A4C70( void *ptr, unsigned int size );
void func_800A4CBC( int status );
int func_800A4F74( struct timeval *tp, ... );

unsigned int func_800A4A18( void *ptr, unsigned int size, unsigned int nitems, FILE *stream );
int func_800A4AD8( FILE *stream );
void *func_800A4B14( void *s1, void *s2, unsigned int n );
int func_800A4BB4( FILE *stream, long offset, int whence );
void *func_800A4CF8( void *s, int c, unsigned int n );
char *func_800A4D84( char *s1, char *s2 );
FILE *func_800A4DD0( char *filename );
double func_800A4E84( double x );
double func_800A4ED4( double x );
double func_800A4F24( double x );

extern FILE D_80107888;

VidStream *func_80089B10( TimeStamp time_stamp, VidStream *vid_stream, int first, XInfo *xinfo );
int func_8008A34C( VidStream *vid_stream, XInfo *xinfo );
int func_8008B560( VidStream *vid_stream );
int func_8008C0A8( VidStream *vid_stream, TimeStamp time_stamp );
int func_8008CDB8( VidStream *vid_stream );

extern const int D_80087A98[64][2];

// The message of func_8008C0A8, "Fatal error. Ring buffer full.": the last thing in the read-only data
// of its object, and declared here for the reason D_800879DC is.
extern char D_80087EE0[];

int func_8008D220( VidStream *vid_stream );

void func_8008F3AC( VidStream *vid_stream, int bnum );
void func_8008F828( VidStream *vid_stream, int bnum, int recon_right_for, int recon_down_for, int zflag );

void func_80091684( VidStream *vid_stream, int bnum, int recon_right_back, int recon_down_back, int zflag );
void func_800933BC( VidStream *vid_stream, int bnum, int recon_right_for, int recon_down_for,
                    int recon_right_back, int recon_down_back, int zflag );

void func_80094064( VidStream *vid_stream );
void func_80094578( VidStream *vid_stream );
void func_80095664( unsigned char *source, unsigned char *dest, int row, int col, int row_size, int right,
                    int down, int right_half, int down_half, int width );
void func_800962DC( VidStream *vid_stream, XInfo *xinfo );
void func_8009646C( BOOLEAN val );
void func_8009649C( BOOLEAN val );


extern const int D_80087C98[64];
extern const int D_80087D98[8][8];

// parseblock.c
void func_800964D0( int n, VidStream *vid_stream );
void func_800983D4( int n, VidStream *vid_stream );

// PENDING: declarations as the imported sources had them, replaced unit by unit
extern s32 D_80086CD0[];
extern s32 D_80086D10;
extern s32 D_80086D18;
extern s32 D_80086D20;
extern s32 D_80086D28;
extern s32 D_80086D2C;
extern s32 D_80086D30;
extern s32 D_80086D34;
extern s32 D_80086D38;
extern s32 D_80086D3C;
extern s32 D_80086D40;
extern f64 D_80086D48;
extern s32 D_80086D50;
extern s32 D_80086D60[];
extern s32 D_80087160[];
extern s32 D_80087560[];
extern f64 D_800FD098[][8];
extern s32 D_800FD298;
extern s32 D_800FD29C;
extern s32 D_800FD2A0;
extern s32 D_800FD2A4;
extern s32 D_800FD2A8;
extern s16 D_800FD2C8[][64];
extern s32 *D_800FF2C8;
extern s32 *D_800FF2CC;
extern s32 *D_800FF2D0;
extern s32 *D_800FF2D4;
extern s32 *D_800FF2D8;
extern s32 *D_800FF2E8;
extern s32 *D_800FF2EC;
extern s32 *D_800FF2F0;
extern s32 D_801033F8;
extern s32 D_801033FC;
extern s32 D_80103404;
extern s32 D_80103408;
extern s32 D_8010340C;
extern s32 D_80103414;
extern s32 D_80103418;
extern s32 D_8010341C;
extern s32 D_80103420;
extern s32 D_80103458;
extern s32 D_8010345C;
extern s32 *D_80103460;
extern s32 D_80103464;
extern s32 D_80103468;
extern s32 *D_8010346C;
extern s32 *D_80103470;
extern s32 D_80103474;
extern s32 D_80103478;
extern s32 D_801034C0;
extern s32 D_801034C4;
extern s32 D_801034F8;
extern s32 D_801034FC;
extern s32 D_80107480;
extern s32 D_80107484;
extern s32 D_80107488;
extern s32 D_80107880;
extern s32 D_801078A4;
extern s32 D_801078A8;
extern s32 D_801078AC;
extern s32 D_801078B0;
extern s32 D_801078B4;
extern s32 *D_801084A0;
extern s32 *D_801084A8;
void func_800998E0( s32 arg0, s32 arg1, s32 arg2 );
void func_80099C8C( s32 arg0, s32 arg1, s32 arg2 );
void func_8009A038( void );
void func_8009A7D0( void );
void func_8009AF48( void );
void func_8009BAE0( void );
void func_8009C5AC( void );
void func_8009C600( void );
void func_8009C754( s32 arg0 );
void func_8009CA80( s32 arg0, s32 arg1 );
void func_8009CAD8( s32 arg0, s32 arg1 );
void func_8009D3D8( void );
void func_8009D4B8( s32 arg0, s32 arg1 );
void func_8009D67C( s32 arg0 );
s32 func_800A19D8( u32 arg0 );
u32 func_800A1A74( u32 arg0 );
s32 func_800A1AE0( s32 arg0 );
s32 func_800A1B60( u32 arg0 );
void func_800A1BE4( s32 arg0 );
void func_800A2594( s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5 );
s32 func_800A2B08( s32 arg0, s32 arg1 );
s32 func_800A2B40( s32 arg0 );
void func_800A2D38( s32 arg0 );
void func_800A2D84( s32 arg0 );
s32 func_800A3168( s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4 );
s32 func_800A3460( s32 arg0, s32 arg1 );
s32 func_800A3808( s32 arg0, s32 arg1 );
s32 func_800A38F8( s32 arg0 );
s32 func_800A3A3C( s32 arg0, s32 arg1, s32 arg2 );
s32 func_800A3B40( s32 arg0 );
s32 func_800A3E00( s32 arg0, s32 arg1 );
void func_800A46FC( void *arg0, s8 *arg1, s32 *arg2 );
void func_800A4804( void *arg0, s8 *arg1, s32 *arg2 );
void func_800A4888( u8 *arg0, s32 *arg1 );
s32 func_800A4920( u8 arg0, s32 arg1, s32 arg2 );

#endif // MPEG_PROTO_H
