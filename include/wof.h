// wof.h -- types, globals and functions shared by the game's units

#ifndef WOF_H
#define WOF_H

#include <ultra64.h>
#include <PR/sched.h>

//
// The audio manager (func_800032A8 to func_80003FDC) is the audiomgr.c of the SDK's demos. The
// binary holds none of its names; the types, their members and the constants below carry the
// names of that source (guess: from the lineage), in the SDK's style.
//
#define MAX_UPDATES         48
#define MAX_EVENTS          48
#define MAX_VOICES          32
#define MAX_CHANNELS        32
#define MAX_SOUNDS          32
#define AUDIO_HEAP_SIZE     200000
#define OUTPUT_RATE         22050
#define MAX_MESGS           8
#define QUIT_MSG            10
#define EXTRA_SAMPLES       80
#define NUM_OUTPUT_BUFFERS  3
#define NUM_ACMD_LISTS      2
#define MAX_RSP_CMDS        4096
#define DMA_BUFFER_LENGTH   0x800
#define NUM_DMA_BUFFERS     36
#define NUM_DMA_MESSAGES    32
#define FRAME_LAG           1
#define AUDIO_STACKSIZE     0x2000

// the demos' debug print, which their header turns off
#define PRINTF( args )

typedef struct {
    u32 outputRate;
    u32 framesPerField;
    u32 maxACMDSize;
} amConfig;

typedef union {
    struct {
        short type;
    } gen;
    struct {
        short               type;
        struct AudioInfo_s  *info;
    } done;
    OSScMsg app;
} AudioMsg;

typedef struct AudioInfo_s {
    short       *data;          // output data pointer
    short       frameSamples;   // number of samples synthesized in this frame
    OSScTask    task;           // scheduler structure
    AudioMsg    msg;            // completion message
} AudioInfo;

typedef struct {
    Acmd        *ACMDList[NUM_ACMD_LISTS];
    AudioInfo   *audioInfo[NUM_OUTPUT_BUFFERS];
    OSThread    thread;
    OSMesgQueue audioFrameMsgQ;
    OSMesg      audioFrameMsgBuf[MAX_MESGS];
    OSMesgQueue audioReplyMsgQ;
    OSMesg      audioReplyMsgBuf[MAX_MESGS];
    ALGlobals   g;
} AMAudioMgr;

typedef struct {
    ALLink  node;
    u32     startAddr;
    u32     lastFrame;
    char    *ptr;
} AMDMABuffer;

typedef struct {
    u8          initialized;
    AMDMABuffer *firstUsed;
    AMDMABuffer *firstFree;
} AMDMAState;

// What a proc's handler returns to DoProcs: w[1] says what becomes of the proc (0: it ends,
// 1: it sleeps w[0] frames, 2 and 3: it waits for event w[0]). The third word is not read.
struct n64dk_r12 {
    s32 w[3];
};

// A proc: a task with a message queue. DoProcs runs each proc's handler once a frame.
// The procs are D_800B82A0[70]; entry 0 only heads the list of live procs.
typedef struct proc_s {
    /* 0x00 */ struct n64dk_r12 ( *unk_00 )( struct proc_s *proc );  // handler; 0 if free
    /* 0x04 */ s32              unk_04;
    /* 0x08 */ s32              unk_08;
    /* 0x0C */ s32              unk_0C;
    /* 0x10 */ s32              unk_10;
    /* 0x14 */ s32              unk_14;
    /* 0x18 */ s32              count;          // messages waiting in items
    /* 0x1C */ s32              items[5];
    /* 0x30 */ void             *unk_30;        // its data: each kind of proc has its own struct
    /* 0x34 */ s32              unk_34;
    /* 0x38 */ s32              unk_38;
    /* 0x3C */ u8               unk_3C[0x4];
    /* 0x40 */ struct proc_s    *next;
} proc_t;   // size 0x44

// An obj: something DrawObjs draws each frame.
// The objs are D_800B40C8[100]; entry 0 only heads the list of live objs.
typedef struct obj_s {
    /* 0x00 */ s32              index;          // its entry in D_800B40C8 and in the matrix arrays
    /* 0x04 */ s32              unk_04;
    /* 0x08 */ s32              unk_08;
    /* 0x0C */ s32              ( *unk_0C )();  // draw function: ( obj, frame )
    /* 0x10 */ s16              x;
    /* 0x12 */ s16              y;
    /* 0x14 */ s16              z;
    /* 0x18 */ f32              scale;
    /* 0x1C */ u8               unk_1C[0xC];
    /* 0x28 */ f32              unk_28;         // unk_28..unk_30: guRotateRPY r, p, h
    /* 0x2C */ f32              unk_2C;
    /* 0x30 */ f32              unk_30;
    /* 0x34 */ u8               unk_34[0x8];
    /* 0x3C */ s32              unk_3C;
    /* 0x40 */ u8               unk_40[0x4];
    /* 0x44 */ s32              unk_44;
    /* 0x48 */ s32              unk_48;
    /* 0x4C */ s32              unk_4C;
    /* 0x50 */ struct obj_s     *next;
} obj_t;    // size 0x54

// the data of the proc that animates Vanna (InitVannaAnim creates it)
typedef struct {
    /* 0x00 */ obj_t *obj;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s16 *unk_08;         // its pictures: unk_18 of the clip_t
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 unk_28;
} vannaAnim_t;    // size 0x2C

// A picture func_8002741C draws: where it goes and how big it is. The tables of them start at
// D_80058548; what lies behind the size is not named yet.
typedef struct {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
    /* 0x08 */ s32 width;
    /* 0x0C */ s32 height;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
} image_t;    // size 0x28


// One of the MPEG movies on the cartridge: D_80058228[38]. func_80021908 loads one.
typedef struct {
    /* 0x00 */ s32 rom;         // where it is on the cartridge
    /* 0x04 */ s32 unk_04;      // if above 0, the proc that plays the movie puts it in D_800B8294
    /* 0x08 */ s32 *size;       // points at its size in bytes, less one
    /* 0x0C */ s32 unk_0C;      // 1, 2 or 3: what func_8009CEC0 is told about it
} movie_t;    // size 0x10

// One line of a menu: a label, and options of which one is chosen. A line holds numbers of
// pictures in the image_t table of its menu. The menus are D_800584C8[4], D_80058868[2],
// D_80058AA8[4], D_80058E70[2] and D_80058FC8[2].
typedef struct {
    /* 0x00 */ s32  unk_00;                     // 0: the cursor passes the line by
    /* 0x04 */ s32  unk_04;                     // the first picture of the label
    /* 0x08 */ s32  unk_08;                     // how many pictures the label has
    /* 0x0C */ s32  unk_0C;                     // the first picture of the first option
    /* 0x10 */ s32  rows;                       // how many options
    /* 0x14 */ s32  cols;                       // how many pictures an option has
    /* 0x18 */ s32  sel;                        // the chosen option
    /* 0x1C */ void ( *callback )( s32 line );  // called when the cursor comes to the line
} menuItem_t;    // size 0x20

// The data of the procs that run a menu (handlers func_800232AC, func_80023CA4, func_80024370,
// func_80024868 and func_80025150), and of the four helpers that move its cursor. The name is
// from the ROM message "MainMenu1 Proc: button press invalid".
typedef struct {
    /* 0x00 */ u8  unk_00[0x4];
    /* 0x04 */ s32 sel;         // the chosen option of the line the cursor is on
    /* 0x08 */ s32 index;       // the line the cursor is on
    /* 0x0C */ s32 delay;       // frames until the stick moves the cursor again
} mainMenu_t;    // size 0x10
// The picture of a letter of the alphabet as func_8002C094 shows the letter chosen:
// D_8005BCC8[26].
typedef struct {
    /* 0x00 */ s32 unk_00;      // what unk_20 of the image_t becomes
    /* 0x04 */ s32 width;
    /* 0x08 */ s32 height;
} letterImage_t;    // size 0xC

// A run of pictures that the MPEG player decodes into memory once, to be shown one at a time:
// what a contestant or Vanna does. D_8005C3B8[6][2] and D_8005C568[6][2] are those of the six
// contestants, D_8005C718[6] those shown where a contestant is chosen, D_8005C7F0[6] those of
// Vanna.
typedef struct {
    /* 0x00 */ s32 width;
    /* 0x04 */ s32 height;
    /* 0x08 */ s32 count;       // how many pictures; 0: there is no such run
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s16 *unk_18;     // the pictures, once they are decoded
    /* 0x1C */ s32 movie;       // its number in D_80058228
    /* 0x20 */ s32 *unk_20;     // what D_800B81E4 is while it is decoded
} clip_t;    // size 0x24

// three coordinates: where func_800323C4 puts a contestant's obj
typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
} vec_t;    // size 0xC

// The sounds of one of the six contestants a player can be: D_8005A3E4[6]. func_80024D60 copies
// them into unk_0FC to unk_110 of the player_t, in this order.
typedef struct {
    /* 0x00 */ s32 unk_00;      // the first of 26 sounds: the letters, as the contestant calls them
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;      // -1: the contestant has none
} voice_t;    // size 0x18

// One of the three contestants: D_800B9990[3].
typedef struct {
    /* 0x000 */ s32 unk_000;
    /* 0x004 */ s32 unk_004;
    /* 0x008 */ s32 unk_008;
    /* 0x00C */ s32 unk_00C;
    /* 0x010 */ s32 unk_010;
    /* 0x014 */ s32 unk_014;
    /* 0x018 */ s32 unk_018;
    /* 0x01C */ u8 unk_01C[0x14];
    /* 0x030 */ u8 unk_030[10][0x14];
    /* 0x0F8 */ s32 unk_0F8;
    /* 0x0FC */ s32 unk_0FC;
    /* 0x100 */ s32 unk_100;
    /* 0x104 */ s32 unk_104;
    /* 0x108 */ s32 unk_108;
    /* 0x10C */ s32 unk_10C;
    /* 0x110 */ s32 unk_110;
} player_t;    // size 0x114

// What one frame is drawn from: the matrices of each obj, by obj index, the display list, and
// room for pictures that are made at run time. It is segment 2 of the display list, and the
// draw functions get the one in use. guess: the Dynamic of the SDK demos, from the lineage of
// func_800057A8.
typedef struct {
    /* 0x00000 */ Mtx projection;         // guess: projection and viewing are the names of the Dynamic
    /* 0x00040 */ Mtx viewing;
    /* 0x00080 */ u8  unk_00080[0xC0];
    /* 0x00140 */ Mtx scale[100];
    /* 0x01A40 */ Mtx translate[100];
    /* 0x03340 */ Mtx rotate[100];
    /* 0x04C40 */ u8  unk_04C40[0x40];
    /* 0x04C80 */ Mtx unk_04C80;
    /* 0x04CC0 */ Gfx glist[3048];
    /* 0x0AC00 */ s16 unk_0AC00[6][64 * 64];    // six pictures of 64 by 64
    /* 0x16C00 */ s16 unk_16C00[64 * 96];
    /* 0x19C00 */ s16 unk_19C00[0x2400];        // each screen lays out its own pictures here
} frame_t;  // size 0x1E400

// A frame and the task that draws it: D_800BEF08[2], and D_800B61A0 says which is in use.
// guess: the GFXInfo of the SDK demos, whose createGfxTask func_800057A8 descends from.
typedef struct {
    /* 0x00000 */ OSScTask task;
    /* 0x00058 */ frame_t  frame;
    /* 0x1E458 */ OSScMsg  msg;             // what the scheduler answers when the task is done
    /* 0x1E478 */ void     *framebuffer;
} gfxInfo_t;    // size 0x1E480

// What guLookAt is given for one frame of a camera move. D_8005EB48[] is the move of the
// opening, and D_800BA5D8 points at the one in use.
typedef struct {
    /* 0x00 */ f32 eyeX;
    /* 0x04 */ f32 eyeY;
    /* 0x08 */ f32 eyeZ;
    /* 0x0C */ f32 atX;
    /* 0x10 */ f32 atY;
    /* 0x14 */ f32 atZ;
    /* 0x18 */ f32 upX;
    /* 0x1C */ f32 upY;
    /* 0x20 */ f32 upZ;
} camera_t;    // size 0x24

// A place func_80016944 puts the camera obj, by number: D_80057F50[].
typedef struct {
    /* 0x00 */ s32      x;
    /* 0x04 */ s32      y;
    /* 0x08 */ s32      z;
    /* 0x0C */ f32      unk_0C;     // unk_0C..unk_14: what the unk_28..unk_30 of the obj become
    /* 0x10 */ f32      unk_10;
    /* 0x14 */ f32      unk_14;
    /* 0x18 */ camera_t *path;      // if not 0, a move that a proc (func_80016734) plays
    /* 0x1C */ s32      count;      // the frames of the move
} view_t;    // size 0x20

// The rumble of one controller's pak: D_800BEE60[4]. func_800051B4 starts it.
typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ s32 unk_0C;
} rumble_t;    // size 0x10


// What func_80004E50, func_80004EB0 and func_80004F0C send the rumble thread: D_800BCA30.
typedef struct {
    /* 0x00 */ u16 type;        // 0: stop the motor, 1: start it, 2: start the pak over
    /* 0x04 */ s32 index;       // the controller
} rumbleMsg_t;    // size 0x8

// The puzzles a kind of round draws from: range of them, starting at puzzle base.
typedef struct {
    /* 0x00 */ s32 base;
    /* 0x04 */ s32 range;
} puzzleRange_t;    // size 0x8
// One wedge of the wheel: D_800B39B8[].
typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s8 name[0x14];
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
} wedge_t;    // size 0x20

// The display lists of one wedge of the wheel. D_80057F08[7] points at the 24 of each kind of
// round.
typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;      // if not 0, drawn in its place once the wedge has unk_1C set
} wedgeDl_t;    // size 0x8

// One puzzle of the built-in list: D_8004BB98[].
typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
} puzzle_t;    // size 0xC

// The entries of D_80057808[]; what they describe is not known yet.
typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ f32 unk_08;
} data80057808_t;    // size 0xC

// The entries of D_80057BB0[].
typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u8 unk_10[0x8];
} layer_t;    // size 0x18

// One square of the puzzle board. The four rows are D_800B9D08[12], D_800B9E58[14],
// D_800B9FE0[14] and D_800BA168[12].
typedef struct {
    /* 0x00 */ s32 unk_00;      // its display list
    /* 0x04 */ u8  *unk_04;     // the picture it shows
    /* 0x08 */ u8  *unk_08;     // the picture of its letter, shown once the square is turned
    /* 0x0C */ s32 unk_0C;      // not 0: it blinks
    /* 0x10 */ s32 unk_10;      // the frames one blink takes
    /* 0x14 */ s32 unk_14;      // the frames left of this blink
    /* 0x18 */ s32 unk_18;      // its colour
} tile_t;    // size 0x1C

// the data of the proc whose handler is func_8000BEA8
typedef struct {
    /* 0x00 */ obj_t *unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u8 unk_08[0x4];
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
} data8000BEA8_t;    // size 0x18

// the data of the proc whose handler is func_8000C310
typedef struct {
    /* 0x00 */ obj_t *unk_00;
} data8000C310_t;    // size 0x4

// the data of the proc whose handler is func_8000C50C
typedef struct {
    /* 0x00 */ obj_t *unk_00;
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ s32 unk_08;
} data8000C50C_t;    // size 0xC

// the data of the proc whose handler is func_8000C6C4
typedef struct {
    /* 0x00 */ obj_t *pos;
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ s32 unk_08;
} data8000C6C4_t;    // size 0xC

// the data of the proc whose handler is func_8000C8A8
typedef struct {
    /* 0x00 */ obj_t *cam;
} data8000C8A8_t;    // size 0x4

// the data of the proc whose handler is func_8000EF68
typedef struct {
    /* 0x00 */ u8 unk_00[0xC];
    /* 0x0C */ f32 unk_0C;
} data8000EF68_t;    // size 0x10

// the data of the proc whose handler is func_8000F274, created by func_80016310 
typedef struct {
    /* 0x00 */ obj_t *actor;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ s32 unk_08;
} data8000F274_t;    // size 0xC

// the data of the proc whose handler is func_8000F84C
typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
} data8000F84C_t;    // size 0x8

// the data of the proc whose handler is func_8000FC3C
typedef struct {
    /* 0x00 */ obj_t *unk_00;
    /* 0x04 */ u8 unk_04[0x8];
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
} data8000FC3C_t;    // size 0x14

// the data of the proc whose handler is func_8000FDFC
typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
} data8000FDFC_t;    // size 0x8

// the data of the proc whose handler is func_8000FFE0
typedef struct {
    /* 0x00 */ obj_t *unk_00;
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ s32 unk_08;
} data8000FFE0_t;    // size 0xC

// the data of the proc whose handler is func_800101F4
typedef struct {
    /* 0x00 */ obj_t *unk_00;
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ s32 unk_08;
} data800101F4_t;    // size 0xC

// the data of the proc whose handler is func_800103B4
typedef struct {
    /* 0x00 */ obj_t *unk_00;
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ s32 unk_08;
} data800103B4_t;    // size 0xC

// the data of the proc whose handler is func_80010574
typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 row;
    /* 0x08 */ s32 col;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u8 letter;
} data80010574_t;    // size 0x14

// the data of the proc whose handler is func_80010D3C
typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 row;
    /* 0x08 */ s32 col;
    /* 0x0C */ u8 unk_0C[0x8];
    /* 0x14 */ u8 *text;
} data80010D3C_t;    // size 0x18

// the data of the proc whose handler is func_80016734
typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ camera_t *unk_08;    // the move it plays
    /* 0x0C */ s32 unk_0C;          // the frame it is at
    /* 0x10 */ s32 unk_10;          // how many frames the move has
} data80016734_t;    // size 0x14

// the data of the proc whose handler is func_80017938, created by func_80017C00
typedef struct {
    /* 0x00 */ u8  unk_00[0x4];
    /* 0x04 */ s32 unk_04;      // the player whose turn it was made in
} data80017938_t;    // size 0x8

// The data of a player proc: the proc of a turn, whose handler is func_80019AAC for a person
// and func_8001C584 for the machine, and the procs a turn makes for its steps, to which it
// copies player, and from func_8001C584 unk_0C as well, through this struct: func_80017DBC,
// func_800183A8, func_80018D28, func_8001933C, func_80019630, func_8001AE18, func_8001B6BC,
// func_8001BC44 and func_8001BED8. func_80017DBC is made by both kinds of turn. The name is
// from the ROM message "Status Proc: player proc does not exist", which func_8002CBF4 prints
// when no proc of this class answers.
typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 player;      // the contestant: 0, 1 or 2
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ s8  unk_10;
} playerProc_t;    // size 0x14

// the data of the proc whose handler is func_80021744, created by func_80021C8C 
typedef struct {
    /* 0x00 */ obj_t *unk_00;
    /* 0x04 */ u8 unk_04[0xC];
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ u8 unk_14[0xC];
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
} data80021744_t;    // size 0x28

// the data of the proc whose handler is func_80029098
typedef struct {
    /* 0x00 */ obj_t *unk_00;
    /* 0x04 */ s32 unk_04;
} data80029098_t;    // size 0x8

// the data of the proc whose handler is func_80029C98
typedef struct {
    /* 0x00 */ u8 unk_00[0x10];
    /* 0x10 */ s32 unk_10;
} data80029C98_t;    // size 0x14

// the data of the proc whose handler is func_8002B318
typedef struct {
    /* 0x00 */ u8 unk_00[0x8];
    /* 0x08 */ s32 step;
} data8002B318_t;    // size 0xC

// the data of the proc whose handler is func_8002C094
typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u8 unk_0C[0x8];
    /* 0x14 */ s32 unk_14;
} data8002C094_t;    // size 0x18

// the data of the proc whose handler is func_8002EFC0
typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x8];
    /* 0x0C */ f32 unk_0C;
} data8002EFC0_t;    // size 0x10

// The data of the procs that time something out: handlers func_8002F338, func_8002F7CC,
// func_8002F94C and func_8002FB60. The four are procs of one class (0x07) that keep the same
// thing in the same place and share no helper; the ROM calls the third the "Solve Timer Proc"
// (in func_8002FD8C), which is where the name is from.
typedef struct {
    /* 0x00 */ u8  unk_00[0x4];
    /* 0x04 */ s32 start;       // when it was started or reset, in seconds since the boot
} timer_t;    // size 0x8

// the data of the proc whose handler is func_800345E8
typedef struct {
    /* 0x00 */ u8  unk_00[0x4];
    /* 0x04 */ s32 unk_04;      // counts down from 10, a step a frame
} data800345E8_t;    // size 0x8

// the data of the proc whose handler is func_80033A28
typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
} data80033A28_t;    // size 0xC

// The data of the procs that move a cursor over the letters: handlers func_8002CBF4,
// func_8002D930 and func_8002E0C8, and the helpers they share.
typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 index;
    /* 0x08 */ u8 unk_08[0x4];
    /* 0x0C */ s32 unk_0C;
} cursor_t;    // size 0x10

// the data of the proc whose handler is func_80021548, created by func_800219B8
typedef struct {
    /* 0x00 */ obj_t *unk_00;
    /* 0x04 */ u8 unk_04[0x1C];
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
} data80021548_t;    // size 0x28

// The data of a contestant animation proc (handler func_800315FC), which InitAnim creates: the
// name is from the ROM messages "InitAnim: ..." in func_800323C4 and func_800325D0.
typedef struct {
    /* 0x00 */ obj_t *obj;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s16 *unk_08;         // its pictures: unk_18 of the clip_t
    /* 0x0C */ u8 unk_0C[0x4];
    /* 0x10 */ s32 frame;
    /* 0x14 */ u8 unk_14[0x4];
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ u8 unk_20[0x4];
    /* 0x24 */ s32 step;
    /* 0x28 */ s32 timer;
} anim_t;    // size 0x2C

// the data of the proc whose handler is func_80034028, created by func_800343F8
typedef struct {
    /* 0x00 */ obj_t *sprite;
    /* 0x04 */ s32 frame;
    /* 0x08 */ s32 timer;
    /* 0x0C */ u8 unk_0C[0x4];
    /* 0x10 */ s32 count;
    /* 0x14 */ f32 x;
    /* 0x18 */ f32 y;
    /* 0x1C */ f32 vx;
    /* 0x20 */ f32 vy;
} data80034028_t;    // size 0x24

//
// Addresses in segment 1, the display list and picture data the game loads. A Gfx one is a
// display list, from what draws it; a u8 one a picture of four bits a pixel, a u16 one a picture
// of sixteen, from the texture image command they are given to. An s32 one is still a
// placeholder: its uses have not been read for its kind.
//
extern s32 D_01010FA0;
extern s32 D_01017550;
extern s32 D_01017650;
extern s32 D_01017750;
extern s32 D_010178D0;
extern s32 D_01017A50;
extern s32 D_01017BD0;
extern Gfx D_010217E0[];
extern Gfx D_010218C8[];
extern Gfx D_01021948[];
extern s32 D_01021970;
extern Gfx D_010219C8[];
extern s32 D_01021A20;
extern s32 D_01021A70;
extern s32 D_01021AC8;
extern s32 D_01024340;
extern s32 D_01024368;
extern s32 D_010308D0;
extern s32 D_01035FA8;
extern s32 D_010367A8;
extern s32 D_01036FA8;
extern s32 D_01037090;
extern s32 D_01037178;
extern s32 D_01037E70;
extern s32 D_01037EB0;
extern s32 D_01037EF0;
extern s32 D_01092090;
extern s32 D_010920D8;
extern s32 D_01092120;
extern s32 D_01092168;
extern s32 D_01093D50;
extern u8 D_010A1B88[];
extern u8 D_010A1F88[];
extern u8 D_010A2388[];
extern u8 D_010A2788[];
extern u8 D_010A2B88[];
extern u8 D_010A3388[];
extern u8 D_010A3788[];
extern s32 D_010A6098;
extern s32 D_010B3728;
extern s32 D_010E3748;
extern s32 D_010E4260;
extern Gfx D_010FA038[];
extern s32 D_0112BBA8;
extern Gfx D_011356C0[];
extern s32 D_01135878;
extern Gfx D_011358C0[];
extern Gfx D_01135908[];
extern s32 D_01135FF8;
extern s32 D_01136080;
extern s32 D_01136108;
extern Gfx D_0113A9B0[];
extern Gfx D_0113A9D0[];
extern s32 D_0113AD08;
extern s32 D_0113AD28;
extern s32 D_0113AD48;
extern s32 D_0113AE28;
extern s32 D_01146E68;
extern u16 D_01157868[];
extern u16 D_01158068[];
extern u16 D_01158868[];
extern u16 D_01159068[];
extern u16 D_01159868[];
extern u16 D_0115B068[];
extern u16 D_0115B868[];
extern u16 D_0115C068[];
extern u16 D_0115C868[];
extern u16 D_0115D068[];
extern s32 D_01166598;
extern s32 D_01166928;
extern s32 D_01166BF8;
extern s32 D_011696A0;
extern s32 D_0116C028;
extern s32 D_01176C88;
extern s32 D_01176CC8;
extern s32 D_01176D08;
extern Gfx D_01197D78[];

//
// string literals that cannot be written as literals until their unit is merged: the unit's
// read-only data starts in an earlier function, which fixes where this one's strings and jump
// tables fall
//
extern char D_80001594[];   // "MainMenu1 Proc: button press invalid\n", in func_800232AC
extern char D_800019BC[];   // "InitAnim: cannot find contestant obj", in func_80033150

//
// globals, in address order
//
extern long long int D_800349B8[];  // rspbootTextStart
extern long long int D_80034A88[];  // rspbootTextEnd, and the start of the graphics microcode
extern long long int D_80037298[];  // aspMainTextStart
extern ALSndPlayer *D_8004B718;
extern s32 D_8004B71C[];            // the parameters of the custom reverb
extern u32 D_8004B7A8;              // audFrameCt
extern u32 D_8004B7AC;              // nextDMA
extern u32 D_8004B7B0;              // curAcmdList
extern s32 D_8004B7B4;
extern Lights6 D_8004B7B8;          // the lights of every scene
extern s32 D_8004B830;
extern s32 D_8004B838;
extern s32 D_8004B83C;
extern s32 D_8004B840;
extern s32 D_8004B844;
extern s32 D_8004B848[];
extern s32 D_8004B860[];
extern s32 D_8004B8C0[];
extern s32 D_8004B920[];
extern s32 D_8004B980[];
extern s32 D_8004B9E0;
extern s8 D_8004B9FC[];
extern s8 D_8004BA04[];
extern puzzle_t D_8004BB98[];
extern s32 D_80057800;
extern data80057808_t D_80057808[];
extern s32 D_800578B0[];
extern s32 D_80057910[];
extern s32 D_80057970[][3];
extern s32 D_80057988[];
extern u8 *D_800579BC[];           // the pictures of the letters, by character
extern s32 D_800579F0[];            // D_800579F0 to D_80057A90: the display lists of the squares of each row
extern s32 D_80057A20[];
extern s32 D_80057A58[];
extern s32 D_80057A68[];
extern s32 D_80057A90[];
extern s32 D_80057B50[][8];
extern layer_t D_80057BB0[];
extern wedgeDl_t *D_80057F08[];
extern s32 D_80057F24[];
extern s32 D_80057F34[];
extern f32 D_80057F44;
extern s32 D_80057F48;
extern view_t D_80057F50[];
extern s32 D_800581F0[];
extern s32 D_800581F4;
extern s32 D_800581FC[];
extern s32 D_80058208;
extern s32 D_80058220;
extern movie_t D_80058228[];
extern char D_80058488[];           // "You are the BIG winner!"
extern s32 D_800584A0[][2];         // [5], x and y of pictures 2 to 6 of the first menu
extern menuItem_t D_800584C8[];
extern image_t D_80058548[];
extern menuItem_t D_80058868[];
extern s32 D_800588A8[][3][2];      // [3], for each contestant unk_20 and unk_24 of pictures 0, 7 and 8 of D_800588F0
extern image_t D_800588F0[];
extern menuItem_t D_80058AA8[];
extern image_t D_80058B28[];
extern menuItem_t D_80058E70[];
extern image_t D_80058EB0[];
extern menuItem_t D_80058FC8[];
extern image_t D_80059008[];
extern image_t D_80059120[];
extern vec_t D_8005A390;
extern vec_t D_8005A39C[];
extern voice_t D_8005A3E4[];
extern vec_t D_8005A474[];
extern u8 D_8005A498[][10];
extern image_t D_8005A4B8[][2];
extern image_t D_8005A5A8[];
extern image_t D_8005A620[];
extern image_t D_8005A760[];
extern image_t D_8005A7B0[];
extern image_t D_8005A828[];
extern s32 D_8005A8C8[];
extern s32 D_8005A930[];
extern image_t D_8005A998[];
extern s32 D_8005ACE8[];
extern image_t D_8005ADD0[][7];
extern s32 D_8005B088[];
extern s32 D_8005B118[];
extern s32 D_8005B148[];
extern s32 D_8005B170;
extern s32 D_8005B174;
extern s32 D_8005B178[];
extern image_t D_8005B1A8[];
extern image_t D_8005B2C0[];
extern image_t D_8005B310[];
extern image_t D_8005B360[];
extern image_t D_8005B4C8[];
extern s32 *D_8005B5A4[];
extern image_t D_8005B630[];
extern image_t D_8005B710[];
extern s32 D_8005BA80[];
extern image_t D_8005BAC0[];
extern letterImage_t D_8005BCC8[];
extern image_t D_8005BE00[];
extern s32 D_8005C1E8[];
extern s32 D_8005C33C[];
extern u8 D_8005C394[];
extern s32 D_8005C3A0[][2];         // [3], unk_48 and unk_4C of the obj of each contestant
extern clip_t D_8005C3B8[][2];
extern clip_t D_8005C568[][2];
extern clip_t D_8005C718[];
extern clip_t D_8005C7F0[];
extern s32 D_8005C8C8[];
extern s32 D_8005C8FC[];
extern s32 D_8005C908[];
extern s32 D_8005C90C[];
extern s32 D_8005C948[];
extern f32 D_8005C958;
extern f32 D_8005C95C;
extern camera_t D_8005EB48[];
extern s32 D_8006DCD8;
extern s32 D_8006DCE8;
extern s32 D_8006DCEC;
extern s32 D_8006DCF0;
extern s32 D_8006DCF4;
extern s32 D_8006DCF8;
extern s32 D_8006DD04;
extern s32 D_8006DD08;
extern s32 D_8006DD0C;
extern s32 D_8006DDC4;
extern long long int D_80082BC8[];  // the data of the graphics microcode at D_80034A88
extern long long int D_80083BC8[];  // aspMainDataStart
extern u64 D_80084218;
extern s32 D_80085108[];
extern s32 D_800851C8[];
extern s32 D_80085208[];
extern s32 D_80085288[];
extern s32 D_80085308;
extern s32 D_8008530C;
extern s32 D_80085310[];
extern u16 D_800866A0[];
extern u16 D_800868A0[];
extern u16 D_800868C0[];
extern u16 D_800868C8[];
extern u16 D_800868D0[];
extern u16 D_80086AD0[];
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
extern s32 D_80086D58;
extern s32 D_80086D60[];
extern s32 D_80087160[];
extern s32 D_80087560[];
extern s32 D_800879DC;
extern s32 D_80087C98[];
extern f64 D_80087E98;
extern u8 D_80087EA0[];
extern s32 D_80087EE0;
extern ALCSeq *D_800A507C[];
extern ALSndpConfig D_800A5084;
extern ALInstrument *D_800A5090;    // the first instrument of the bank: its sounds are the sound effects
extern ALSound *D_800A5098;
extern ALSndId *D_800A509C;         // [MAX_SOUNDS], -1 where no sound is allocated
extern u64 D_800A50A0[];            // audioStack: AUDIO_STACKSIZE bytes
extern OSContStatus D_800A70A0[];
extern OSContPad D_800A70B0[];
extern OSScMsg D_800A70C8;          // the message of the controller event
extern OSThread D_800A70E8;         // the rumble thread, func_80004F6C
extern u64 D_800A7298[];            // its stack: 0x2000 bytes
extern OSThread D_800A9298;         // the controller thread, func_80004160
extern u64 D_800A9448[];            // its stack: 0x2000 bytes
extern OSPfs D_800AB448[];          // [MAXCONTROLLERS]
extern s32 D_800AB5E8;
extern u64 D_800AB5F0[];            // the stack of the thread D_800AD950: 0x2000 bytes
extern OSThread D_800AD5F0;         // the main thread, func_800065D4
extern OSThread D_800AD7A0;         // the idle thread, func_800063A0
extern OSThread D_800AD950;         // the game thread, func_800067D8
extern u64 D_800ADB00[];            // the stack of the idle thread: 0x2000 bytes
extern OSMesg D_800AFB00[];          // [200], the messages of the PI manager
extern OSMesgQueue D_800AFE20;      // the queue of the PI manager
extern OSMesgQueue D_800AFE38;      // where func_80006828 waits for its read
extern OSMesg D_800AFE50;
extern s32 D_800AFE58;
extern OSMesgQueue D_800B3970;      // the queue of the controller events
extern OSScClient D_800B3988;
extern ALBankFile *D_800B3990;
extern s32 D_800B3994;
extern ALBankFile *D_800B3998;      // NOTE: nothing sets it
extern f32 D_800B39A0[][2];         // [3], for each player what the buttons have added to unk_28 and unk_2C of the camera
extern wedge_t D_800B39B8[];
extern s32 D_800B3CB8;
extern u64 D_800B3CC0[];            // the stack of the graphics microcode: SP_DRAM_STACK_SIZE8 bytes
extern s32 D_800B40C0;
extern s32 D_800B40C4;
extern obj_t D_800B40C8[];
extern s32 D_800B40D4;
extern s32 D_800B4118;
extern s32 D_800B6198;
extern s32 D_800B619C;
extern s32 D_800B61A0;
extern s32 D_800B61A4;
extern s32 D_800B61A8;
extern s8 D_800B61AA[];
extern f32 D_800B61AC;
extern s8 D_800B61B0[];
extern u8 D_800B61B5;
extern s32 D_800B61B8;
extern s32 D_800B61C0;
extern s32 D_800B61D8;
extern u64 D_800B61E0[];            // the yield buffer of the graphics task: 0x900 bytes
extern s32 D_800B6AE0;
extern s32 D_800B6AE8[][16];
extern f32 D_800B6BE8;
extern f32 D_800B6BEC;
extern f32 D_800B6BF0;
extern OSMesg D_800B6BF4;
extern u8 D_800B6BF8[][0x50];       // [70], the data blocks of the procs: AllocBlock hands them out
extern ALSeqFile *D_800B81D8;
extern s32 D_800B81DC;
extern s32 D_800B81E0;
extern s32 *D_800B81E4;
extern Gfx *D_800B81E8;
extern s32 D_800B81F0[];
extern s32 D_800B8290;
extern s32 D_800B8294;
extern f32 D_800B8298;
extern proc_t D_800B82A0[];
extern s32 D_800B82E0;
extern s32 D_800B9538;
extern s32 D_800B953C;
extern s32 D_800B9540;
extern u8 D_800B9544[];
extern u8 D_800B9559[][21];
extern u8 D_800B95AD[][21];
extern u8 D_800B9601[][21];
extern s8 D_800B9655[];
extern u8 D_800B966A[];
extern OSMesgQueue D_800B9688;      // where the scheduler answers the graphics tasks and sends the retraces
extern s32 D_800B96A0;
extern s32 D_800B96A4;
extern s32 D_800B96A8;
extern u32 D_800B96AC;
extern u16 D_800B96B0;
extern s32 D_800B96B4;
extern s32 D_800B96B8;
extern u32 D_800B96BC;              // minFrameSize
extern s32 D_800B96C0;
extern u8 D_800B96C4;
extern OSSched D_800B96C8;
extern u32 D_800B9950;              // maxFrameSize
extern OSContPad D_800B9954;
extern ALHeap D_800B9960;
extern s32 D_800B9974;
extern s32 D_800B9980;
extern s32 D_800B9984;
extern s32 D_800B9988;
extern s16 *D_800B998C;
extern player_t D_800B9990[];
extern OSMesgQueue D_800B9CD0;
extern s32 D_800B9CEC;
extern s32 D_800B9CF0;
extern s32 D_800B9CF4;
extern s32 D_800B9CF8;
extern s32 D_800B9CFC;
extern s32 D_800B9D00;
extern s32 D_800B9D04;
extern tile_t D_800B9D08[];
extern tile_t D_800B9E58[];
extern tile_t D_800B9FE0[];
extern tile_t D_800BA168[];
extern s32 D_800BA2BC;
extern s32 D_800BA2C0;
extern AMDMABuffer D_800BA2C8[];     // dmaBuffs[NUM_DMA_BUFFERS]
extern OSMesgQueue D_800BA598;       // audDMAMessageQ
extern s32 D_800BA5B0;
extern AMDMAState D_800BA5C8;        // dmaState
extern s32 D_800BA5D4;
extern camera_t *D_800BA5D8;
extern s32 D_800BA5E0[];
extern u64 D_800BA6F8[];            // the stack of the scheduler: OS_SC_STACKSIZE bytes
extern u16 D_800BC6F8;
extern s32 D_800BC6FC;
extern OSIoMesg D_800BC700[];       // audDMAIOMesgBuf[NUM_DMA_MESSAGES]
extern s32 D_800BCA00;
extern s32 D_800BCA04;
extern s32 D_800BCA08;
extern s32 D_800BCA0C;
extern s32 D_800BCA10;
extern s32 D_800BCA14;
extern s32 D_800BCA18;
extern s32 D_800BCA1C;
extern s32 D_800BCA20;
extern s32 D_800BCA24;
extern s32 D_800BCA28;
extern rumbleMsg_t D_800BCA30;
extern OSMesg D_800BCA40[];          // [8], the messages of D_800B9688
extern s32 D_800BCA60;
extern AMAudioMgr D_800BCA68;        // __am
extern f32 D_800BCCF0;
extern s32 D_800BCCF4;
extern s32 D_800BCD50;
extern s32 D_800BCD54;
extern OSScClient D_800BCD58;
extern u32 D_800BCD64;              // frameSize
extern OSMesg D_800BCD68;
extern OSMesgQueue D_800BCD70;      // the queue of the rumble thread
extern u64 D_800BCD88[];            // the stack of the main thread: 0x2000 bytes
extern s32 D_800BED88;
extern ALCSPlayer *D_800BED90[];
extern s32 D_800BED98;
extern u32 D_800BEDA4;              // maxRSPCmds
extern s32 D_800BEDA8;
extern s32 D_800BEDB0[];
extern s32 D_800BEDD8[];
extern u32 D_800BEDE4;
extern s32 D_800BEDE8[];
extern s32 D_800BEDF8;
extern OSMesg D_800BEE00[];          // [8], the messages of D_800B9CD0
extern s32 D_800BEE20;
extern s32 D_800BEE24;
extern s32 D_800BEE28;
extern f32 D_800BEE2C;
extern f32 D_800BEE30;
extern f32 D_800BEE34;
extern f32 D_800BEE3C;
extern f32 D_800BEE40;
extern f32 D_800BEE44;
extern s32 D_800BEE48;
extern s32 D_800BEE4C;
extern s32 D_800BEE50;
extern s32 D_800BEE54;
extern u16 D_800BEE58[];
extern rumble_t D_800BEE60[];
extern OSMesgQueue *D_800BEEA0;      // the command queue of the scheduler
extern s32 D_800BEEA8[][8];
extern gfxInfo_t D_800BEF08[];
extern s32 D_800FB808;
extern s32 D_800FB80C;
extern u64 D_800FB810;
extern OSMesg D_800FB818[];          // audDMAMessageBuf[NUM_DMA_MESSAGES]
extern u8 D_800FC098[];
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
extern s32 D_80107888;
extern s32 D_8010788C;
extern s32 D_80107890;
extern s32 D_801078A4;
extern s32 D_801078A8;
extern s32 D_801078AC;
extern s32 D_801078B0;
extern s32 D_801078B4;
extern s32 *D_801084A0;
extern s32 *D_801084A8;
extern s32 D_8038F800;
extern s32 D_803B5000;
extern s32 D_803DA800;
extern puzzleRange_t D_B025D810[];  // on the cartridge, read in place

//
// functions, in address order: the unit boundaries are not known yet
//
void func_80002348( void );
void func_80002598( s32 seqNo, s32 player );
void func_800026B0( s32 arg0 );
s32 func_80002700( void );
void func_800028E4( void );
void func_80002B34( void );
s32 func_80002C34( s32 arg0 );
s32 func_80002CE0( s32 arg0 );
void func_80002F58( s32 arg0 );
void func_80003014( s32 arg0, s32 arg1, s32 arg2, s32 arg3 );
void func_800030E8( s32 arg0, f32 arg1 );
void func_8000315C( void );
s32 func_80003234( void );
s32 func_8000326C( void );
void func_800032A8( ALSynConfig *c, OSPri pri, amConfig *amc );
void func_800037A0( void *arg );
u32 func_80003944( AudioInfo *info, AudioInfo *lastInfo );
void func_80003C68( AudioInfo *info );
s32 func_80003CC8( s32 addr, s32 len, void *state );
ALDMAproc func_80003F64( AMDMAState **state );
void func_80003FDC( void );
void func_80004160( void *arg );
void func_8000420C( void );
void func_800045D4( void );
void func_80004E50( s32 arg0 );
void func_80004EB0( s32 arg0 );
void func_80004F0C( s32 arg0 );
void func_80004F6C( void *arg );
void func_80005258( void );
void func_80005300( s32 arg0 );
void func_80005624( void );
void func_80005700( void );
void func_800057A8( gfxInfo_t *info );
void func_80005FD0( s32 arg0 );
void func_800060B0( s32 arg0 );
void func_80006328( void );
void func_800063A0( void *arg );
void func_8000648C( void );
void func_800065D4( void *arg );
void func_800067D8( void *arg );
void func_80006828( s32 arg0, s32 arg1, s32 arg2 );
void func_800068F0( void );
void func_80006B28( void );
void func_80006B58( void );
void func_80006BFC( void );
void func_80006E54( s32 arg0, s32 arg1 );
s32 func_800076E0( s32 arg0 );
s32 func_80007818( s32 arg0 );
s32 func_80007888( s32 arg0, s32 arg1 );
void func_80007DAC( s32 arg0 );
s32 func_80007EEC( s32 arg0 );
s32 func_800082E4( void );
s32 func_800084E8( void );
f32 func_80008628( void );
void func_800087F8( void );
s32 func_800088E4( void );
void func_80008AB8( void );
void func_80008F64( void );
void func_80009108( f32 arg0 );
s32 func_8000928C( void );
void func_80009364( s32 arg0 );
void func_80009494( void );
void func_8000963C( s32 arg0 );
s32 func_80009748( s32 arg0, s32 arg1, s32 arg2 );
s32 func_80009804( s32 arg0, s32 arg1 );
s32 func_80009900( s32 arg0, s32 arg1 );
s32 func_800099B0( s32 arg0, s32 arg1 );
s32 func_80009A74( s32 arg0 );
void func_80009AE0( s32 arg0, s32 arg1 );
s32 func_80009C98( s32 arg0 );
void func_80009D08( s32 arg0 );
s32 func_80009D2C( s32 arg0 );
void func_80009D78( s32 arg0 );
void func_80009F38( char *arg0 );
void func_80009F98( s32 arg0 );
void func_80009FD8( void );
s32 func_8000A0E4( void );
s32 func_8000A158( s32 arg0 );
s32 func_8000A204( void );
void *func_8000A31C( s32 arg0 );
void func_8000A408( s32 arg0 );
s32 func_8000A4A4( s32 arg0, s32 arg1 );
s32 func_8000A56C( s32 arg0, s32 arg1 );
void func_8000A664( void );
void func_8000A850( s32 arg0 );
s32 func_8000A990( s32 arg0, s32 arg1 );
s32 func_8000AA24( s32 arg0, s32 arg1, s32 arg2 );
void func_8000AAB0( s32 arg0, s32 arg1, s32 arg2 );
void func_8000ABB8( s32 arg0, s32 arg1, s32 arg2, s32 arg3 );
s32 func_8000ACE8( proc_t *proc );
void func_8000AD9C( s32 arg0 );
void func_8000ADEC( s32 arg0 );
void func_8000AE70( s32 arg0, s32 arg1, s32 arg2 );
void func_8000AF00( void );
s32 func_8000AFEC( void );
s32 func_8000B060( s32 arg0 );
s32 func_8000B10C( void );
s32 func_8000B234( s32 arg0 );
void func_8000B2D4( s32 arg0 );
s32 func_8000B3B0( s32 arg0, s32 arg1, s32 arg2 );
void func_8000B468( s32 arg0 );
void func_8000B528( s32 arg0 );
s32 func_8000B5DC( s32 arg0, s32 arg1 );
s32 func_8000B670( s32 arg0, s32 arg1, s32 arg2 );
void func_8000B6FC( s32 arg0, s32 arg1 );
void func_8000B780( void );
s32 func_8000B7F4( s32 arg0 );
void func_8000B89C( s32 arg0 );
s32 func_8000B924( s32 arg0 );
s32 func_8000B978( void );
void func_8000B9FC( s32 arg0 );
void func_8000BAA8( void );
void func_8000BB10( void );
void func_8000BB68( void );
void func_8000BBA8( void );
struct n64dk_r12 func_8000BC64( s32 arg1 );
void func_8000BE6C( void );
struct n64dk_r12 func_8000BEA8( s32 arg1 );
struct n64dk_r12 func_8000C310( s32 arg1 );
struct n64dk_r12 func_8000C50C( s32 arg1 );
struct n64dk_r12 func_8000C6C4( s32 arg1 );
struct n64dk_r12 func_8000C8A8( s32 arg1 );
void func_8000CB58( s32 arg0, s32 arg1 );
void func_8000D400( s32 arg0, s32 arg1 );
void func_8000D6D8( s32 arg0, s32 arg1 );
void func_8000D8B8( s32 arg0, s32 arg1 );
void func_8000DCA0( s32 arg0, s32 arg1 );
void func_8000DF2C( s32 arg0, s32 arg1 );
struct n64dk_r12 func_8000E4B0( s32 arg1 );
void func_8000E6B4( void );
void func_8000E738( void );
void func_8000E794( void );
void func_8000E7D4( void );
struct n64dk_r12 func_8000EB40( s32 arg1 );
void func_8000EE50( s32 arg0, s32 arg1 );
void func_8000EE78( void );
struct n64dk_r12 func_8000EF68( s32 arg1 );
struct n64dk_r12 func_8000F274( s32 arg1 );
struct n64dk_r12 func_8000F740( s32 arg1 );
struct n64dk_r12 func_8000F84C( s32 arg1 );
struct n64dk_r12 func_8000FC3C( s32 arg1 );
struct n64dk_r12 func_8000FDFC( s32 arg1 );
struct n64dk_r12 func_8000FFE0( s32 arg1 );
struct n64dk_r12 func_800101F4( s32 arg1 );
struct n64dk_r12 func_800103B4( s32 arg1 );
struct n64dk_r12 func_80010574( s32 arg1 );
void func_80010AB8( s32 arg0 );
struct n64dk_r12 func_80010D3C( s32 arg1 );
s32 func_800111F0( s32 arg0, s32 arg1, s32 arg2 );
void func_80011304( s32 arg0, s32 arg1, s32 arg2 );
void func_8001142C( s32 arg0, s32 arg1, u8 arg2 );
void func_80011620( void );
void func_80011780( void );
void func_80011920( void );
void func_80011B24( void );
void func_80011F58( void );
struct n64dk_r12 func_8001228C( s32 arg1 );
void func_80012500( s32 arg0, s32 arg1 );
s32 func_8001277C( tile_t *arg0 );
void func_80012838( tile_t *tiles, s32 count, s32 arg2 );
void func_80012D40( s32 arg0, s32 arg1 );
void func_800132EC( s32 arg0 );
void func_800133C8( void );
s32 func_80013440( s32 arg0 );
void func_80013500( s32 arg0 );
void func_80013748( s32 arg0, s32 arg1 );
void func_80014208( s32 arg0, s32 arg1 );
void func_800144F0( s32 arg0, s32 arg1 );
void func_80014768( s32 arg0, s32 arg1 );
void func_80014A5C( s32 arg0, s32 arg1 );
void func_80014F38( s32 arg0, s32 arg1 );
void func_800153C4( s32 arg0, s32 arg1 );
obj_t *func_80015848( proc_t *proc, s32 arg1, s32 arg2, s32 arg3 );
void func_80015940( s32 *arg0, tile_t *tiles, s32 row, s32 count );
void func_80015D4C( void );
void func_80015EDC( s32 *arg0, tile_t *tiles, s32 row, s32 count );
void func_80016008( void );
void func_80016098( void );
void func_800161A8( void );
void func_80016310( void );
s32 func_80016638( void );
s32 func_800166C0( void );
struct n64dk_r12 func_80016734( s32 arg1 );
void func_80016944( obj_t *obj, s32 arg1 );
void func_80016B9C( s32 arg0 );
struct n64dk_r12 func_80016BEC( s32 arg1 );
void func_80016C78( s32 arg0, s32 arg1 );
void func_8001745C( s32 arg0 );
void func_800174DC( void );
s32 func_80017548( void );
void func_80017678( void );
s32 func_80017728( void );
void func_800177A4( void );
void func_80017848( void );
struct n64dk_r12 func_80017938( s32 arg1 );
void func_80017C00( s32 arg0, s32 arg1 );
struct n64dk_r12 func_80017DBC( s32 arg1 );
struct n64dk_r12 func_800181A4( s32 arg1 );
struct n64dk_r12 func_800183A8( s32 arg1 );
struct n64dk_r12 func_80018D28( s32 arg1 );
struct n64dk_r12 func_8001933C( s32 arg1 );
struct n64dk_r12 func_80019630( s32 arg1 );
struct n64dk_r12 func_80019AAC( s32 arg1 );
void func_8001A424( s32 arg0 );
void func_8001A484( void );
void func_8001A5D0( void );
void func_8001A628( s32 arg0 );
s32 func_8001A6DC( s32 arg0 );
s32 func_8001A7A8( s32 arg0 );
s32 func_8001A894( f32 arg0, s32 arg1 );
s32 func_8001A97C( f32 arg0 );
void func_8001AA60( s32 arg0 );
struct n64dk_r12 func_8001AE18( s32 arg1 );
struct n64dk_r12 func_8001B6BC( s32 arg1 );
struct n64dk_r12 func_8001BC44( s32 arg1 );
struct n64dk_r12 func_8001BED8( s32 arg1 );
struct n64dk_r12 func_8001C584( s32 arg1 );
void func_8001D320( s32 arg0 );
void func_8001D3CC( s32 arg0 );
void func_8001D440( s32 arg0, s32 arg1 );
void func_8001DAF0( s32 arg0, s32 arg1 );
void func_8001ED48( s32 arg0 );
void func_8001EFF0( s32 arg0, s32 arg1 );
void func_80020150( s32 arg0, s32 arg1 );
void func_800202A0( s32 arg0 );
void func_800206C8( s32 arg0 );
void func_80020C98( s32 arg0 );
void func_80021090( s32 arg0 );
obj_t *func_800211E4( proc_t *proc, char *arg1, f32 x, f32 y, s32 arg4 );
void func_800212C0( proc_t *proc );
void func_800213CC( proc_t *proc );
struct n64dk_r12 func_80021548( s32 arg1 );
struct n64dk_r12 func_80021744( s32 arg1 );
s32 func_80021908( s32 arg0 );
void func_800219B8( s32 arg0, s32 arg1, s32 arg2, s32 arg3 );
void func_80021B04( s32 arg0, s32 arg1 );
void func_80021B4C( s32 arg0, s32 arg1, s16 *arg2, s32 *arg3 );
void func_80021C8C( s32 arg0, s32 *arg1, obj_t *arg2, s32 arg3, s32 arg4 );
void func_80021E28( void );
void func_80021E88( s32 arg0, s32 arg1 );
void func_8002208C( s32 arg0, s32 arg1 );
void func_80022218( s32 arg0, s32 arg1 );
void func_800223A4( s32 arg0, s32 arg1 );
void func_80022530( s32 arg0, s32 arg1 );
void func_800226BC( image_t *images, s32 count, s32 arg2 );
void func_80022784( proc_t *proc, image_t *images, menuItem_t *item, s32 arg3 );
void func_800229D0( proc_t *proc, image_t *images, menuItem_t *items, s32 count );
void func_80022BC8( proc_t *proc, image_t *images, menuItem_t *items, s32 count );
void func_80022DC0( proc_t *proc, image_t *images, menuItem_t *item, s32 arg3 );
void func_80022FE0( proc_t *proc, image_t *images, menuItem_t *item, s32 arg3 );
void func_80023200( void );
struct n64dk_r12 func_800232AC( proc_t *proc );
void func_80023B44( void );
struct n64dk_r12 func_80023CA4( proc_t *proc );
struct n64dk_r12 func_80024370( proc_t *proc );
struct n64dk_r12 func_80024868( proc_t *proc );
void func_80024D60( s32 arg0 );
void func_8002500C( void );
struct n64dk_r12 func_80025150( proc_t *proc );
void func_800258BC( void );
void func_80025FA8( void );
void func_800263DC( void );
void func_80026800( void );
void func_80026DEC( void );
void func_80026E50( void );
void func_80026EB4( void );
void func_80026FD4( void );
s32 func_80027218( s32 arg0, s32 arg1, s32 arg2, s32 arg3 );
s32 func_8002731C( image_t *image, s32 arg1 );
void func_8002741C( s32 arg0, s32 arg1, s32 arg2, s32 arg3 );
void func_800278A8( s32 arg0, s32 arg1 );
void func_800278F0( s32 arg0, s32 arg1 );
void func_80027F3C( s32 arg0, s32 arg1 );
void func_80028064( s32 arg0, s32 arg1 );
void func_80028194( s32 arg0, s32 arg1 );
void func_8002842C( s32 arg0, s32 arg1 );
void func_80028554( s32 arg0, s32 arg1 );
void func_8002867C( s32 arg0, s32 arg1 );
void func_800287A4( s32 arg0, s32 arg1 );
void func_800288CC( s32 arg0, s32 arg1 );
void func_800289F4( s32 arg0, s32 arg1 );
void func_80028B1C( s32 arg0, s32 arg1 );
void func_80028C4C( proc_t *proc );
void func_80028CC4( void );
void func_80028D3C( s32 arg0, s32 arg1 );
struct n64dk_r12 func_80029098( s32 arg1 );
void func_80029440( void );
void func_80029974( s32 arg0 );
void func_80029BFC( s32 arg0 );
struct n64dk_r12 func_80029C98( s32 arg1 );
void func_8002A014( void );
void func_8002A538( void );
void func_8002A8C8( s32 arg0, s32 arg1 );
void func_8002AAD0( s32 arg0, s32 arg1, s32 arg2 );
void func_8002ACE8( s32 arg0 );
void func_8002AE60( s32 arg0 );
void func_8002AFDC( void );
void func_8002B054( void );
struct n64dk_r12 func_8002B094( s32 arg1 );
struct n64dk_r12 func_8002B318( s32 arg1 );
struct n64dk_r12 func_8002B730( s32 arg1 );
struct n64dk_r12 func_8002B904( s32 arg1 );
struct n64dk_r12 func_8002BA44( s32 arg1 );
struct n64dk_r12 func_8002BCF4( s32 arg1 );
struct n64dk_r12 func_8002BE84( s32 arg1 );
struct n64dk_r12 func_8002C094( s32 arg1 );
void func_8002CAB4( void );
struct n64dk_r12 func_8002CBF4( s32 arg1 );
void func_8002D8B0( s32 arg0 );
struct n64dk_r12 func_8002D930( s32 arg1 );
s32 func_8002DF80( void );
s32 func_8002E064( void );
struct n64dk_r12 func_8002E0C8( s32 arg1 );
void func_8002EB40( void );
void func_8002EB90( s32 arg0 );
void func_8002EBF4( void );
void func_8002EC60( void );
void func_8002EDC0( void );
void func_8002EDE0( void );
struct n64dk_r12 func_8002EFC0( s32 arg1 );
struct n64dk_r12 func_8002F338( s32 arg1 );
struct n64dk_r12 func_8002F7CC( s32 arg1 );
struct n64dk_r12 func_8002F94C( s32 arg1 );
struct n64dk_r12 func_8002FB60( s32 arg1 );
void func_8002FCD8( void );
void func_8002FD14( void );
void func_8002FD50( void );
void func_8002FD8C( void );
void func_8002FE2C( void );
void func_8002FE70( void );
void func_8002FEB0( s32 arg0, s32 arg1 );
void func_80030490( s32 arg0, s32 arg1 );
void func_80030B5C( s32 arg0, s32 arg1 );
void func_80031340( s16 *arg0, s32 arg1 );
void func_8003143C( s16 *arg0, s32 arg1 );
struct n64dk_r12 func_800315FC( s32 arg1 );
struct n64dk_r12 func_80031A54( s32 arg1 );
void func_800323C4( s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4 );
void func_800325D0( s32 arg0, s32 arg1 );
void func_80032858( void );
s32 func_8003288C( s32 arg0, s32 arg1 );
void func_80032AD4( s32 arg0 );
void func_80032B10( void );
void func_80032B80( void );
void func_80032BF0( void );
s32 func_80033150( s32 arg0, s32 arg1, s32 arg2 );
void func_80033334( void );
void func_800334E4( void );
void func_800335D0( void );
struct n64dk_r12 func_80033688( s32 arg1 );
void func_800339E8( void );
struct n64dk_r12 func_80033A28( s32 arg1 );
void func_80033CBC( void );
void func_80033CF8( s32 arg0, s32 arg1 );
struct n64dk_r12 func_80034028( s32 arg1 );
void func_800343F8( s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6,
                    s32 arg7 );
struct n64dk_r12 func_800345E8( s32 arg1 );

void func_80034950( void );
void func_800887D8( s32 arg0 );
s32 func_800888C0( s32 arg0, s32 arg1, s32 arg2 );
s32 func_80088A2C( s32 arg0 );
s32 func_80088C58( s32 arg0 );
s32 func_800890C8( s32 arg0 );
f64 func_80089490( void );
void func_800894F8( void );
s32 func_800895C4( s32 arg0 );
void func_80089898( s32 arg0 );
s32 func_80089984( s32 arg0, s32 arg1 );
s32 func_80089B10( s32 arg0, s32 arg1, s32 arg2, s32 arg3 );
s32 func_8008A34C( s32 arg0, s32 arg1 );
s32 func_8008B560( s32 arg0 );
s32 func_8008C0A8( s32 arg0, s32 arg1 );
s32 func_8008CDB8( s32 arg0 );
s32 func_8008D220( s32 arg0 );
void func_8008F3AC( s32 arg0, s32 arg1 );
void func_8008F828( s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4 );
void func_80091684( s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4 );
void func_800933BC( s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6 );
void func_80094064( s32 arg0 );
void func_80094578( s32 arg0 );
void func_80095664( s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6,
                    s32 arg7, s32 arg8, s32 arg9 );
void func_800962DC( s32 arg0, s32 arg1 );
void func_8009646C( s32 arg0 );
void func_8009649C( s32 arg0 );
void func_800964D0( s32 arg0, s32 arg1 );
void func_800983D4( s32 arg0, s32 arg1 );
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
void func_8009CEC0( s32 arg0, s32 arg1 );
s32 func_8009D244( void );
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
s32 func_800A4A18( s32 arg0, s32 arg1, s32 arg2, s32 arg3 );
s32 func_800A4AD8( s32 arg0 );
s32 func_800A4B14( s32 arg0, s32 arg1, s32 arg2 );
s32 func_800A4BB4( s32 arg0, s32 arg1, s32 arg2 );
void func_800A4C04( s32 arg0 );
s32 func_800A4C28( s32 arg0 );
s32 func_800A4C70( s32 arg0, s32 arg1 );
void func_800A4CBC( s32 arg0 );
s32 func_800A4CF8( s32 arg0, s32 arg1, s32 arg2 );
s32 func_800A4D84( s32 arg0, s32 arg1 );
s32 *func_800A4DD0( s32 arg0 );
void func_800A4E58( s32 arg0 );
f64 func_800A4E84( f64 arg0 );
f64 func_800A4ED4( f64 arg0 );
f64 func_800A4F24( f64 arg0 );
s32 func_800A4F74( s32 arg0, ... );

#endif // WOF_H
