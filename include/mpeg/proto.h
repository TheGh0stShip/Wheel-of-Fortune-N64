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
void correct_underflow( VidStream *vid_stream );
int next_bits( int num, unsigned int mask, VidStream *vid_stream );
char *get_ext_data( VidStream *vid_stream );
int next_start_code( VidStream *vid_stream );
char *get_extra_bit_info( VidStream *vid_stream );

// The message of correct_underflow, "Unexpected read error.". It is the last thing in its object's
// read-only data, and retail's fill behind it is not zero (stale bytes of the assembler's buffer), so
// the gate cannot place a literal there: it compares the literal's own padding with that fill.
extern char D_800879DC[];

// video.c
double ReadSysClock( void );
void InitCrop( void );
VidStream *NewVidStream( unsigned int buffer_len );
void ResetVidStream( VidStream *vid );
PictImage *NewPictImage( VidStream *vid_stream, XInfo *xinfo );
VidStream *mpegVidRsrc( TimeStamp time_stamp, VidStream *vid_stream, int first, XInfo *xinfo );
int ParseSeqHead( VidStream *vid_stream, XInfo *xinfo );
int ParseGOP( VidStream *vid_stream );
int ParsePicture( VidStream *vid_stream, TimeStamp time_stamp );
int ParseSlice( VidStream *vid_stream );
int ParseMacroBlock( VidStream *vid_stream );
void ReconIMBlock( VidStream *vid_stream, int bnum );
void ReconPMBlock( VidStream *vid_stream, int bnum, int recon_right_for, int recon_down_for, int zflag );
void ReconBMBlock( VidStream *vid_stream, int bnum, int recon_right_back, int recon_down_back, int zflag );
void ReconBiMBlock( VidStream *vid_stream, int bnum, int recon_right_for, int recon_down_for,
                    int recon_right_back, int recon_down_back, int zflag );
void ProcessSkippedPFrameMBlocks( VidStream *vid_stream );
void ProcessSkippedBFrameMBlocks( VidStream *vid_stream );
void ReconSkippedBlock( unsigned char *source, unsigned char *dest, int row, int col, int row_size, int right,
                    int down, int right_half, int down_half, int width );
void DoPictureDisplay( VidStream *vid_stream, XInfo *xinfo );
void SetBFlag( BOOLEAN val );
void SetPFlag( BOOLEAN val );

extern const int zigzag[64][2];
extern const int zigzag_direct[64];
extern const int scan[8][8];

// The message of ParsePicture, "Fatal error. Ring buffer full.": the last thing in the read-only data
// of its object, and declared here for the reason D_800879DC is.
extern char D_80087EE0[];

// parseblock.c
void ParseReconBlock( int n, VidStream *vid_stream );
void ParseAwayBlock( int n, VidStream *vid_stream );

// motionvector.c
void ComputeForwVector( int *recon_right_for_ptr, int *recon_down_for_ptr, VidStream *the_stream );
void ComputeBackVector( int *recon_right_back_ptr, int *recon_down_back_ptr, VidStream *the_stream );

// decoders.c
void init_mb_addr_inc( void );
void init_mb_type_P( void );
void init_mb_type_B( void );
void init_motion_vectors( void );
void init_tables( void );

// floatdct.c
void init_float_idct( void );
void float_idct( short *block );

// gdith.c
void InitColorDisplay( char *name, XInfo *xinfo );
void ExecuteDisplay( VidStream *vid_stream, XInfo *xinfo );

// main.c
void DoDitherImage( VidStream *vid_stream );

extern int    loopFlag;
extern int    shmemFlag;
extern int    quietFlag;
extern int    requireKeypressFlag;
extern int    noDisplayFlag;
extern int    framerate;
extern int    partialFlag;
extern int    startFrame;
extern int    endFrame;
extern int    gammaCorrectFlag;
extern int    chromaCorrectFlag;
extern double chromaCorrect;
extern int    qualityFlag;

extern FILE      *input;
extern char      *inputName;
extern VidStream *D_80107884;
extern XInfo     xinfo;

// jrevdct.c
void init_pre_idct( void );
void j_rev_dct_sparse( DCTBLOCK data, int pos );
void j_rev_dct( DCTBLOCK data );

// 16bit.c
void InitColorDither( int thirty2 );
void Color16DitherImage( unsigned char *lum, unsigned char *cr, unsigned char *cb, unsigned char *out, int rows,
                    int cols );

// util32.c
Visual *FindFullColorVisual( Display *dpy, int *depth );

// readfile.c
int get_more_data( VidStream *vid_stream );
void clear_data_stream( VidStream *vid_stream );
void SeekStream( VidStream *vid_stream );
int pure_get_more_data( unsigned int *buf_start, int max_length, int *length_ptr, unsigned int **buf_ptr,
                   VidStream *vid_stream );
int read_sys( VidStream *vid_stream, unsigned int start );
int ReadStartCode( unsigned int *startCode, VidStream *vid_stream );
int find_start_code( FILE *input );
int ReadPackHeader( double *systemClockTime, unsigned long *muxRate, VidStream *vid_stream );
int ReadSystemHeader( VidStream *vid_stream );
int ReadPacket( unsigned char packetID, VidStream *vid_stream );
void ReadTimeStamp( unsigned char *inputBuffer, unsigned char *hiBit, unsigned long *low4Bytes );
void ReadSTD( unsigned char *inputBuffer, unsigned char *stdBufferScale, unsigned long *stdBufferSize );
void ReadRate( unsigned char *inputBuffer, unsigned long *rate );
int MakeFloatClockTime( unsigned char hiBit, unsigned long low4Bytes, double *floatClockTime );

#endif // MPEG_PROTO_H
