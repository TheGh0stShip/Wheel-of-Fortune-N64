// proto.h -- the MPEG player's functions and globals, by the unit that defines them
//
// guess: the file is proto.h of the Berkeley mpeg_play decoder, with the globals that decoder declares in
// video.h. Three functions of the module are declared in wof.h instead, because game code outside the
// player calls them: func_8009CEC0 and func_8009D244 of main.c and func_800A4E58 of libc.c, and with
// them the flag D_80086D58. The functions of the C library are in libc.h.

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
VidStream *func_80089B10( TimeStamp time_stamp, VidStream *vid_stream, int first, XInfo *xinfo );
int func_8008A34C( VidStream *vid_stream, XInfo *xinfo );
int func_8008B560( VidStream *vid_stream );
int func_8008C0A8( VidStream *vid_stream, TimeStamp time_stamp );
int func_8008CDB8( VidStream *vid_stream );
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

extern const int D_80087A98[64][2];
extern const int D_80087C98[64];
extern const int D_80087D98[8][8];

// The message of func_8008C0A8, "Fatal error. Ring buffer full.": the last thing in the read-only data
// of its object, and declared here for the reason D_800879DC is.
extern char D_80087EE0[];

// parseblock.c
void func_800964D0( int n, VidStream *vid_stream );
void func_800983D4( int n, VidStream *vid_stream );

// motionvector.c
void func_800998E0( int *recon_right_for_ptr, int *recon_down_for_ptr, VidStream *the_stream );
void func_80099C8C( int *recon_right_back_ptr, int *recon_down_back_ptr, VidStream *the_stream );

// decoders.c
void func_8009A038( void );
void func_8009A7D0( void );
void func_8009AF48( void );
void func_8009BAE0( void );
void func_8009C5AC( void );

// floatdct.c
void func_8009C600( void );
void func_8009C754( short *block );

// gdith.c
void func_8009CA80( char *name, XInfo *xinfo );
void func_8009CAD8( VidStream *vid_stream, XInfo *xinfo );

// main.c
void func_8009D300( VidStream *vid_stream );

extern int    D_80086D18;
extern int    D_80086D1C;
extern int    D_80086D20;
extern int    D_80086D24;
extern int    D_80086D28;
extern int    D_80086D2C;
extern int    D_80086D30;
extern int    D_80086D34;
extern int    D_80086D38;
extern int    D_80086D3C;
extern int    D_80086D40;
extern double D_80086D48;
extern int    D_80086D50;

extern FILE      *D_8010346C;
extern char      *D_801084A0;
extern VidStream *D_80107884;
extern XInfo     D_801033F8;

// jrevdct.c
void func_8009D3D8( void );
void func_8009D4B8( DCTBLOCK data, int pos );
void func_8009D67C( DCTBLOCK data );

// 16bit.c
void func_800A1BE4( int thirty2 );
void func_800A2594( unsigned char *lum, unsigned char *cr, unsigned char *cb, unsigned char *out, int rows,
                    int cols );

// util32.c
Visual *func_800A2B08( Display *dpy, int *depth );

// readfile.c
int func_800A2B40( VidStream *vid_stream );
void func_800A2D38( VidStream *vid_stream );
void func_800A2D84( VidStream *vid_stream );
int func_800A3168( unsigned int *buf_start, int max_length, int *length_ptr, unsigned int **buf_ptr,
                   VidStream *vid_stream );
int func_800A3460( VidStream *vid_stream, unsigned int start );
int func_800A3808( unsigned int *startCode, VidStream *vid_stream );
int func_800A38F8( FILE *input );
int func_800A3A3C( double *systemClockTime, unsigned long *muxRate, VidStream *vid_stream );
int func_800A3B40( VidStream *vid_stream );
int func_800A3E00( unsigned char packetID, VidStream *vid_stream );
void func_800A46FC( unsigned char *inputBuffer, unsigned char *hiBit, unsigned long *low4Bytes );
void func_800A4804( unsigned char *inputBuffer, unsigned char *stdBufferScale, unsigned long *stdBufferSize );
void func_800A4888( unsigned char *inputBuffer, unsigned long *rate );
int func_800A4920( unsigned char hiBit, unsigned long low4Bytes, double *floatClockTime );

#endif // MPEG_PROTO_H
