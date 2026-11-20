// video.h -- the MPEG player's types: the video stream and the layers of an MPEG-1 sequence
//
// guess: the player descends from the Berkeley mpeg_play decoder (the reentrant 2.3-patched line,
// where the decoder state lives in VidStream and the X state in XInfo). The type, member, macro and
// file names in this module are that decoder's wherever retail's layout and code agree with it; the
// binary itself records none of them.

#ifndef MPEG_VIDEO_H
#define MPEG_VIDEO_H

#include "mpeg/libc.h"

typedef int            INT32;
typedef short          INT16;
typedef char           INT8;
typedef unsigned int   UINT32;
typedef unsigned short UINT16;
typedef unsigned char  UINT8;

// what the parsing functions return
#define SKIP_PICTURE        ( -10 )
#define SKIP_TO_START_CODE  ( -1 )
#define PARSE_OK            1

#define BOOLEAN int
#define TRUE    1
#define FALSE   0

// the number of frames the stream keeps
#define RING_BUF_SIZE 5

// Pict.code_type
#define I_TYPE 1
#define P_TYPE 2
#define B_TYPE 3
#define D_TYPE 4

// start codes
#define SEQ_END_CODE            0x000001b7
#define SEQ_START_CODE          0x000001b3
#define GOP_START_CODE          0x000001b8
#define PICTURE_START_CODE      0x00000100
#define SLICE_MIN_START_CODE    0x00000101
#define SLICE_MAX_START_CODE    0x000001af
#define EXT_START_CODE          0x000001b5
#define USER_START_CODE         0x000001b2
#define SEQUENCE_ERROR_CODE     0x000001b4

// the number of macroblocks one call of mpegVidRsrc parses
#define MB_QUANTUM 100

// macroblock address increments that are not increments
#define MB_STUFFING 34
#define MB_ESCAPE   35

// PictImage.locked
#define DISPLAY_LOCK    0x01
#define PAST_LOCK       0x02
#define FUTURE_LOCK     0x04

// VidStream.ditherType and XInfo.ditherType: the decoder's output formats. The player is built with
// the dithers left out, which leaves the 16-bit colour conversion.
#define HYBRID_DITHER       0
#define HYBRID2_DITHER      1
#define FS4_DITHER          2
#define FS2_DITHER          3
#define FS2FAST_DITHER      4
#define Twox2_DITHER        5
#define GRAY_DITHER         6
#define FULL_COLOR_DITHER   7
#define NO_DITHER           8
#define ORDERED_DITHER      9
#define MONO_DITHER         10
#define MONO_THRESHOLD      11
#define ORDERED2_DITHER     12
#define MBORDERED_DITHER    13
#define GRAY256_DITHER      14
#define PPM_DITHER          15
#define FULL_COLOR2_DITHER  16
#define GRAY2_DITHER        17
#define GRAY2562_DITHER     18

#define IS_2x2_DITHER( a )  ( 0 )

// when a frame is to be shown
typedef int TimeStamp;

// a decoded frame
typedef struct pict_image {
    /* 0x00 */ unsigned char *luminance;    // Y plane: 16 * mb_width by 16 * mb_height
    /* 0x04 */ unsigned char *Cr;           // a quarter of that
    /* 0x08 */ unsigned char *Cb;
    /* 0x0C */ unsigned char *display;      // the converted picture: 4 bytes a pixel
    /* 0x10 */ int           locked;        // DISPLAY_LOCK, PAST_LOCK, FUTURE_LOCK
    /* 0x14 */ TimeStamp     show_time;
} PictImage;    // size 0x18

// group of pictures header
typedef struct GoP {
    /* 0x00 */ BOOLEAN      drop_flag;
    /* 0x04 */ unsigned int tc_hours;       // time code
    /* 0x08 */ unsigned int tc_minutes;
    /* 0x0C */ unsigned int tc_seconds;
    /* 0x10 */ unsigned int tc_pictures;
    /* 0x14 */ BOOLEAN      closed_gop;     // no vectors into the previous group
    /* 0x18 */ BOOLEAN      broken_link;
    /* 0x1C */ char         *ext_data;
    /* 0x20 */ char         *user_data;
} GoP;  // size 0x24

// picture header
typedef struct pict {
    /* 0x00 */ unsigned int temp_ref;
    /* 0x04 */ unsigned int code_type;      // I_TYPE, P_TYPE, B_TYPE, D_TYPE
    /* 0x08 */ unsigned int vbv_delay;
    /* 0x0C */ BOOLEAN      full_pel_forw_vector;
    /* 0x10 */ unsigned int forw_r_size;
    /* 0x14 */ unsigned int forw_f;
    /* 0x18 */ BOOLEAN      full_pel_back_vector;
    /* 0x1C */ unsigned int back_r_size;
    /* 0x20 */ unsigned int back_f;
    /* 0x24 */ char         *extra_info;
    /* 0x28 */ char         *ext_data;
    /* 0x2C */ char         *user_data;
} Pict; // size 0x30

// slice header
typedef struct slice {
    /* 0x00 */ unsigned int vert_pos;
    /* 0x04 */ unsigned int quant_scale;
    /* 0x08 */ char         *extra_info;
} Slice;    // size 0x0C

// the macroblock being decoded
typedef struct macroblock {
    /* 0x00 */ int          mb_address;
    /* 0x04 */ int          past_mb_addr;
    /* 0x08 */ int          motion_h_forw_code;
    /* 0x0C */ unsigned int motion_h_forw_r;
    /* 0x10 */ int          motion_v_forw_code;
    /* 0x14 */ unsigned int motion_v_forw_r;
    /* 0x18 */ int          motion_h_back_code;
    /* 0x1C */ unsigned int motion_h_back_r;
    /* 0x20 */ int          motion_v_back_code;
    /* 0x24 */ unsigned int motion_v_back_r;
    /* 0x28 */ unsigned int cbp;            // coded block pattern
    /* 0x2C */ BOOLEAN      mb_intra;
    /* 0x30 */ BOOLEAN      bpict_past_forw;
    /* 0x34 */ BOOLEAN      bpict_past_back;
    /* 0x38 */ int          past_intra_addr;
    /* 0x3C */ int          recon_right_for_prev;
    /* 0x40 */ int          recon_down_for_prev;
    /* 0x44 */ int          recon_right_back_prev;
    /* 0x48 */ int          recon_down_back_prev;
} Macroblock;   // size 0x4C

// the block being decoded
typedef struct block {
    /* 0x00 */ short int dct_recon[8][8];
    /* 0x80 */ short int dct_dc_y_past;
    /* 0x82 */ short int dct_dc_cr_past;
    /* 0x84 */ short int dct_dc_cb_past;
} Block;    // size 0x86

// the state of one video stream
typedef struct vid_stream {
    /* 0x000 */ unsigned int    h_size;                         // in pixels
    /* 0x004 */ unsigned int    v_size;
    /* 0x008 */ unsigned int    mb_height;                      // in macroblocks
    /* 0x00C */ unsigned int    mb_width;
    /* 0x010 */ unsigned char   aspect_ratio;                   // code
    /* 0x011 */ unsigned char   picture_rate;                   // code
    /* 0x014 */ unsigned int    bit_rate;
    /* 0x018 */ unsigned int    vbv_buffer_size;
    /* 0x01C */ BOOLEAN         const_param_flag;
    /* 0x020 */ unsigned char   intra_quant_matrix[8][8];
    /* 0x060 */ unsigned char   non_intra_quant_matrix[8][8];
    /* 0x0A0 */ char            *ext_data;
    /* 0x0A4 */ char            *user_data;
    /* 0x0A8 */ GoP             group;
    /* 0x0CC */ Pict            picture;
    /* 0x0FC */ Slice           slice;
    /* 0x108 */ Macroblock      mblock;
    /* 0x154 */ Block           block;
    /* 0x1DC */ int             state;
    /* 0x1E0 */ int             bit_offset;                     // bits of *buffer already used
    /* 0x1E4 */ unsigned int    *buffer;                        // the word being read
    /* 0x1E8 */ int             buf_length;                     // words left, this one included
    /* 0x1EC */ unsigned int    *buf_start;
    /* 0x1F0 */ int             max_buf_length;
    /* 0x1F4 */ int             film_has_ended;
    /* 0x1F8 */ int             sys_layer;                      // -1: not known yet, 0: video only, 1: system
    /* 0x1FC */ unsigned int    num_left;                       // bytes of a word ReadPacket left over
    /* 0x200 */ unsigned int    leftover_bytes;
    /* 0x204 */ int             EOF_flag;
    /* 0x208 */ FILE            *input;
    /* 0x20C */ long            seekValue;                      // 0: no seek, > 0: seek there, < 0: done
    /* 0x210 */ BOOLEAN         swap;
    /* 0x214 */ BOOLEAN         Parse_done;
    /* 0x218 */ int             gAudioStreamID;
    /* 0x21C */ int             gVideoStreamID;
    /* 0x220 */ int             gReservedStreamID;
    /* 0x224 */ int             right_for;                      // ReconPMBlock's last vector
    /* 0x228 */ int             down_for;
    /* 0x22C */ int             right_half_for;
    /* 0x230 */ int             down_half_for;
    /* 0x234 */ unsigned int    curBits;                        // the unread bits of *buffer, left-aligned
    /* 0x238 */ int             matched_depth;
    /* 0x23C */ char            *filename;
    /* 0x240 */ int             ditherType;
    /* 0x244 */ char            *ditherFlags;
    /* 0x248 */ int             totNumFrames;
    /* 0x250 */ double          realTimeStart;
    /* 0x258 */ PictImage       *past;
    /* 0x25C */ PictImage       *future;
    /* 0x260 */ PictImage       *current;
    /* 0x264 */ PictImage       *ring[RING_BUF_SIZE];
} VidStream;    // size 0x278

// guess: the X11 types XInfo is made of. The player keeps the decoder's XInfo with its layout (depth
// at 0x64, ditherType at 0x6C) although it has no X server; how the vendor's stand-ins for the X11
// headers spelled these types is not recorded, so they are X11's.
typedef struct _XImage  XImage;
typedef struct _XDisplay Display;
typedef struct _XGC     *GC;
typedef struct _Visual  Visual;
typedef unsigned long   Colormap;
typedef unsigned long   Window;

typedef struct {
    /* 0x00 */ long flags;
    /* 0x04 */ int  x;
    /* 0x08 */ int  y;
    /* 0x0C */ int  width;
    /* 0x10 */ int  height;
    /* 0x14 */ int  min_width;
    /* 0x18 */ int  min_height;
    /* 0x1C */ int  max_width;
    /* 0x20 */ int  max_height;
    /* 0x24 */ int  width_inc;
    /* 0x28 */ int  height_inc;
    struct {
        int x;
        int y;
    } min_aspect, max_aspect;   /* 0x2C, 0x34 */
    /* 0x3C */ int  base_width;
    /* 0x40 */ int  base_height;
    /* 0x44 */ int  win_gravity;
} XSizeHints;   // size 0x48

// where a stream is shown
typedef struct {
    /* 0x00 */ XImage       *ximage;
    /* 0x04 */ Colormap     cmap;
    /* 0x08 */ Window       window;
    /* 0x0C */ GC           gc;
    /* 0x10 */ Display      *display;
    /* 0x14 */ int          owncmFlag;
    /* 0x18 */ XSizeHints   hints;
    /* 0x60 */ Visual       *visual;
    /* 0x64 */ int          depth;
    /* 0x68 */ char         *name;
    /* 0x6C */ int          ditherType;
    /* 0x70 */ Window       ExistingWindow;
} XInfo;    // size 0x74

#define CONST_BITS 13

#define DCTSIZE     8
#define DCTSIZE2    64

typedef short   DCTELEM;
typedef DCTELEM DCTBLOCK[DCTSIZE2];

#endif // MPEG_VIDEO_H
