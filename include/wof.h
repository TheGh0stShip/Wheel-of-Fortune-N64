// wof.h -- types, globals and functions shared by the game's units

#ifndef WOF_H
#define WOF_H

#include <ultra64.h>
#include <PR/sched.h>

//
// The audio manager (amCreateAudioMgr to __clearAudioDMA) is the audiomgr.c of the SDK's demos. The
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

// What one frame is drawn from: the matrices of each obj, by obj index, the display list, and
// room for pictures that are made at run time. It is segment 2 of the display list, and the
// draw functions get the one in use. guess: the Dynamic of the SDK demos, from the lineage of
// createGfxTask.
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

// What a proc's handler returns to DoProcs: w[1] says what becomes of the proc (0: it ends,
// 1: it sleeps w[0] frames, 2 and 3: it waits for event w[0]). The third word is not read.
struct procResult_s {
    s32 w[3];
};

struct proc_s;
struct obj_s;

// A proc's handler: DoProcs calls it once a frame with its proc.
typedef struct procResult_s ( *procHandler_t )( struct proc_s *proc );

// An obj's draw function: DrawObjs calls it once a frame with its obj and the frame being drawn.
typedef void ( *objDraw_t )( struct obj_s *obj, frame_t *frame );

// A proc: a task with a message queue. DoProcs runs each proc's handler once a frame.
// The procs are procst[70]; entry 0 only heads the list of live procs.
typedef struct proc_s {
    /* 0x00 */ procHandler_t    handler;        // 0 if free
    /* 0x04 */ s32              id;             // its number: what its data block and its objs are tagged with
    /* 0x08 */ s32              cls;            // its class, which FindProc and the messages select on
    /* 0x0C */ s32              sleep;          // frames until its handler runs again
    /* 0x10 */ s32              event;          // the event it waits for; -1: any
    /* 0x14 */ s32              waiting;        // not 0: it waits for event
    /* 0x18 */ s32              count;          // messages waiting in items
    /* 0x1C */ s32              items[5];
    /* 0x30 */ union procData_u *data;          // its data block, from AllocBlock
    /* 0x34 */ s32              unk_34;
    /* 0x38 */ s32              unk_38;
    /* 0x3C */ u8               unk_3C[0x4];
    /* 0x40 */ struct proc_s    *next;
} proc_t;   // size 0x44

// An obj: something DrawObjs draws each frame.
// The objs are objst[100]; entry 0 only heads the list of live objs.
typedef struct obj_s {
    /* 0x00 */ s32              index;          // its entry in objst and in the matrix arrays
    /* 0x04 */ s32              owner;          // the id of the proc it belongs to; 0: none
    /* 0x08 */ s32              cls;            // its class, which FindObj selects on
    /* 0x0C */ objDraw_t        draw;           // 0 if free
    /* 0x10 */ s16              x;
    /* 0x12 */ s16              y;
    /* 0x14 */ s16              z;
    /* 0x18 */ f32              scale;
    /* 0x1C */ u8               unk_1C[0xC];
    /* 0x28 */ f32              roll;           // roll, pitch, heading: what guRotateRPY is given
    /* 0x2C */ f32              pitch;
    /* 0x30 */ f32              heading;
    /* 0x34 */ u8               unk_34[0x8];
    /* 0x3C */ Mtx              *mtx;           // a matrix its draw function applies first, if not 0
    /* 0x40 */ u8               unk_40[0x4];
    /* 0x44 */ s32              image;          // the segment address of the picture it shows
    /* 0x48 */ Gfx              *dl;            // its display list
    /* 0x4C */ Gfx              *secondDl;      // a second one, drawn with the second half of the picture
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
    /* 0x20 */ u16 *unk_20;     // the two pictures func_8002731C chooses from; 0: none
    /* 0x24 */ u16 *unk_24;
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
    /* 0x00 */ u16 *unk_00;     // what unk_20 of the image_t becomes
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

// One of the three contestants: players[3].
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

// A frame and the task that draws it: gfxInfo[2], and curGfxInfo says which is in use.
// guess: the GFXInfo of the SDK demos, whose createGfxTask createGfxTask descends from.
typedef struct {
    /* 0x00000 */ OSScTask task;
    /* 0x00058 */ frame_t  frame;
    /* 0x1E458 */ OSScMsg  msg;             // what the scheduler answers when the task is done
    /* 0x1E478 */ void     *framebuffer;
} gfxInfo_t;    // size 0x1E480

// What guLookAt is given for one frame of a camera move. openingPath[] is the move of the
// opening, and curCamera points at the one in use.
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

// A place SetView puts the camera obj, by number: views[].
typedef struct {
    /* 0x00 */ s32      x;
    /* 0x04 */ s32      y;
    /* 0x08 */ s32      z;
    /* 0x0C */ f32      roll;       // roll, pitch, heading: what those of the obj become
    /* 0x10 */ f32      pitch;
    /* 0x14 */ f32      heading;
    /* 0x18 */ camera_t *path;      // if not 0, a move that a proc (CameraPathProc) plays
    /* 0x1C */ s32      count;      // the frames of the move
} view_t;    // size 0x20

// The rumble of one controller's pak: rumbles[4]. StartRumble starts it.
typedef struct {
    /* 0x00 */ s32 present;     // 1 once osMotorInit found a rumble pak
    /* 0x04 */ f32 level;       // what strength has added up to: the motor runs a frame each time it passes 1
    /* 0x08 */ f32 strength;    // added each frame
    /* 0x0C */ s32 frames;      // the frames left
} rumble_t;    // size 0x10


// What StartMotor, StopMotor and ResetMotor send the rumble thread: rumbleMsg.
typedef struct {
    /* 0x00 */ u16 type;        // 0: stop the motor, 1: start it, 2: start the pak over
    /* 0x04 */ s32 index;       // the controller
} rumbleMsg_t;    // size 0x8

// The puzzles a kind of round draws from: range of them, starting at puzzle base.
typedef struct {
    /* 0x00 */ s32 base;
    /* 0x04 */ s32 range;
} puzzleRange_t;    // size 0x8
// One wedge of the wheel: wedges[].
typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s8 name[0x14];
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
} wedge_t;    // size 0x20

// The display lists of one wedge of the wheel. D_80057F08[7] points at the 24 of each kind of
// round.
typedef struct {
    /* 0x00 */ Gfx *unk_00;
    /* 0x04 */ Gfx *unk_04;     // if not 0, drawn in its place once the wedge has unk_1C set
} wedgeDl_t;    // size 0x8

// One puzzle of the built-in list: puzzles[].
typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8  *unk_04;     // its category, which LoadPuzzle copies into category
    /* 0x08 */ s32 unk_08;
} puzzle_t;    // size 0xC

// The entries of D_80057808[]: the display list and the matrix of one of the objs StartOpening
// makes, drawn by func_8000D6D8.
typedef struct {
    /* 0x00 */ Gfx *unk_00;
    /* 0x04 */ Mtx *unk_04;
    /* 0x08 */ f32 unk_08;
} data80057808_t;    // size 0xC

// The entries of D_80057BB0[]. GetLayerColor gives the colour an entry is drawn in: unk_10, or
// unk_14 for the first half of each blink while unk_04 is set.
typedef struct {
    /* 0x00 */ Gfx *unk_00;     // its display list
    /* 0x04 */ s32 unk_04;      // not 0: it blinks
    /* 0x08 */ s32 unk_08;      // the frames one blink takes
    /* 0x0C */ s32 unk_0C;      // the frames left of this blink
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
} layer_t;    // size 0x18

// One square of the puzzle board. The four rows are D_800B9D08[12], D_800B9E58[14],
// D_800B9FE0[14] and D_800BA168[12].
typedef struct {
    /* 0x00 */ Gfx *unk_00;     // its display list
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

// the data of the proc whose handler is WheelPullProc
typedef struct {
    /* 0x00 */ u8 unk_00[0xC];
    /* 0x0C */ f32 unk_0C;
} data8000EF68_t;    // size 0x10

// the data of the proc whose handler is PointerProc, created by InitStage 
typedef struct {
    /* 0x00 */ obj_t *actor;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ s32 unk_08;
} data8000F274_t;    // size 0xC

// the data of the proc whose handler is WheelStopProc, created by TurnWheel
typedef struct {
    /* 0x00 */ obj_t *unk_00;   // NOTE: no obj is made for this proc; the handler reads it all the same
    /* 0x04 */ s32 unk_04;
} data8000F84C_t;    // size 0x8

// The data of the proc whose handler is WheelSpinProc, which ends each frame in TurnWheel
// on the same data. SpinProc, CpuSpinProc and FinalSpinProc create it and put the obj
// of class 0x401 in unk_00.
typedef struct {
    /* 0x00 */ obj_t *unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u8 unk_08[0x4];
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
} data8000FDFC_t;    // size 0x14

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

// the data of the proc whose handler is LightLetterProc
typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 row;
    /* 0x08 */ s32 col;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u8 letter;
} data80010574_t;    // size 0x14

// the data of the proc whose handler is LightTextProc, created by func_8002C094
typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 row;
    /* 0x08 */ s32 col;
    /* 0x0C */ u8 unk_0C[0x8];
    /* 0x14 */ u8 *text;
} data80010D3C_t;    // size 0x18

// the data of the proc whose handler is CameraPathProc, created by SetView
typedef struct {
    /* 0x00 */ obj_t *unk_00;   // NOTE: no obj is made for this proc; the handler reads it all the same
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ camera_t *unk_08;    // the move it plays
    /* 0x0C */ s32 unk_0C;          // the frame it is at
    /* 0x10 */ s32 unk_10;          // how many frames the move has
} data80016734_t;    // size 0x14

// the data of the proc whose handler is AdjustCameraProc, created by SetGameView
typedef struct {
    /* 0x00 */ u8  unk_00[0x4];
    /* 0x04 */ s32 unk_04;      // the player whose turn it was made in
} data80017938_t;    // size 0x8

// The data of a player proc: the proc of a turn, whose handler is PlayerTurnProc for a person
// and CpuTurnProc for the machine, and the procs a turn makes for its steps, to which it
// copies player, and from CpuTurnProc unk_0C as well, through this struct: RoundOverProc,
// SpinProc, BuyVowelProc, SolveProc, FinalSpinTurnProc, CpuSpinProc, CpuBuyVowelProc,
// CpuSolveProc and CpuFinalSpinTurnProc. RoundOverProc is made by both kinds of turn. The name is
// from the ROM message "Status Proc: player proc does not exist", which StatusProc prints
// when no proc of this class answers.
typedef struct {
    /* 0x00 */ u8  unk_00[0x4];
    /* 0x04 */ s32 player;      // the contestant: 0, 1 or 2
    /* 0x08 */ u8  unk_08[0x4];
    /* 0x0C */ f32 unk_0C;
} playerProc_t;    // size 0x10

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


// The data of the procs that time something out: handlers RoundTimerProc, DemoTimerProc,
// SolveTimerProc and func_8002FB60. The four are procs of one class (0x07) that keep the same
// thing in the same place and share no helper; the ROM calls the third the "Solve Timer Proc"
// (in ResetSolveTimer), which is where the name is from.
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

// The data of the procs that move a cursor over the letters: handlers StatusProc,
// LetterPickProc and SolvePuzzleProc, and the helpers they share.
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

// The data block of a proc (unk_30): one of the 0x50-byte blocks of blocks, holding the
// struct of its kind of proc. A proc that has an obj keeps it in the first word: CreatProc's
// callers that make the obj (MakeObj, func_80027218) store it there for every kind.
// guess: a union, which the bytes do not tell from a cast at each use.
typedef union procData_u {
    obj_t           *obj;
    vannaAnim_t     vannaAnim;
    mainMenu_t      mainMenu;
    data8000BEA8_t  data8000BEA8;
    data8000C310_t  data8000C310;
    data8000C50C_t  data8000C50C;
    data8000C6C4_t  data8000C6C4;
    data8000C8A8_t  data8000C8A8;
    data8000EF68_t  data8000EF68;
    data8000F274_t  data8000F274;
    data8000F84C_t  data8000F84C;
    data8000FDFC_t  data8000FDFC;
    data8000FFE0_t  data8000FFE0;
    data800101F4_t  data800101F4;
    data800103B4_t  data800103B4;
    data80010574_t  data80010574;
    data80010D3C_t  data80010D3C;
    data80016734_t  data80016734;
    data80017938_t  data80017938;
    playerProc_t    playerProc;
    data80021744_t  data80021744;
    data80029098_t  data80029098;
    data80029C98_t  data80029C98;
    data8002B318_t  data8002B318;
    timer_t         timer;
    data800345E8_t  data800345E8;
    data80033A28_t  data80033A28;
    cursor_t        cursor;
    data80021548_t  data80021548;
    anim_t          anim;
    data80034028_t  data80034028;
} procData_t;

//
// Addresses in segment 1, the display list and picture data the game loads, typed by what is
// done with them: a Gfx one is drawn as a display list, a Mtx one given to the matrix command,
// a u8 one loaded as a picture of four bits a pixel and a u16 one as a picture of sixteen.
//
extern u16 D_01010FA0[];
extern u16 D_01017550[];
extern u16 D_01017650[];
extern u16 D_01017750[];
extern u16 D_010178D0[];
extern u16 D_01017A50[];
extern u16 D_01017BD0[];
extern Gfx D_010217E0[];
extern Gfx D_010218C8[];
extern Gfx D_01021948[];
extern Gfx D_01021970[];
extern Gfx D_010219C8[];
extern Gfx D_01021A20[];
extern Gfx D_01021A70[];
extern Gfx D_01021AC8[];
extern Gfx D_01024340[];
extern Gfx D_01024368[];
extern Gfx D_010308D0[];
extern u16 D_01035FA8[];
extern u16 D_010367A8[];
extern Gfx D_01036FA8[];
extern Gfx D_01037090[];
extern Gfx D_01037178[];
extern Mtx D_01037E70;
extern Mtx D_01037EB0;
extern Mtx D_01037EF0;
extern Gfx D_01092090[];
extern Gfx D_010920D8[];
extern Gfx D_01092120[];
extern Gfx D_01092168[];
extern Gfx D_01093D50[];
extern u8 D_010A1B88[];
extern u8 D_010A1F88[];
extern u8 D_010A2388[];
extern u8 D_010A2788[];
extern u8 D_010A2B88[];
extern u8 D_010A3388[];
extern u8 D_010A3788[];
extern Gfx D_010A6098[];
extern Gfx D_010B3728[];
extern Gfx D_010E3748[];
extern Gfx D_010E4260[];
extern Gfx D_010FA038[];
extern Gfx D_0112BBA8[];
extern Gfx D_011356C0[];
extern Gfx D_01135878[];
extern Gfx D_011358C0[];
extern Gfx D_01135908[];
extern Gfx D_01135FF8[];
extern Gfx D_01136080[];
extern Gfx D_01136108[];
extern Gfx D_0113A9B0[];
extern Gfx D_0113A9D0[];
extern Gfx D_0113AD08[];
extern Gfx D_0113AD28[];
extern Gfx D_0113AD48[];
extern Mtx D_0113AE28;
extern u16 D_01146E68[];
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
extern Gfx D_01166598[];
extern Gfx D_01166928[];
extern Gfx D_01166BF8[];
extern Gfx D_011696A0[];
extern Gfx D_0116C028[];
extern Mtx D_01176C88;
extern Mtx D_01176CC8;
extern Mtx D_01176D08;
extern Gfx D_01197D78[];

//
// string literals that cannot be written as literals until their unit is merged: the unit's
// read-only data starts in an earlier function, which fixes where this one's strings and jump
// tables fall
//
extern char D_800019BC[];   // "InitAnim: cannot find contestant obj", in func_80033150

//
// globals, in address order
//
extern long long int D_800349B8[];  // rspbootTextStart
extern long long int D_80034A88[];  // rspbootTextEnd, and the start of the graphics microcode
extern long long int D_80037298[];  // aspMainTextStart
extern ALSndPlayer *sndPlayer;
extern s32 D_8004B71C[];            // the parameters of the custom reverb
extern u32 audFrameCt;              // audFrameCt
extern u32 nextDMA;              // nextDMA
extern u32 curAcmdList;              // curAcmdList
extern s32 firstTime;
extern Lights6 D_8004B7B8;          // the lights of every scene
extern s32 D_8004B830;
extern s32 D_8004B838;
extern s32 debugflag;
extern s32 D_8004B840;
extern s32 D_8004B844;
extern s32 D_8004B848[];
extern s32 D_8004B860[];
extern s32 D_8004B8C0[];
extern s32 D_8004B920[];
extern s32 D_8004B980[];
extern u8 alphabet[];          // "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
extern s8 vowelLetters[];
extern s8 consonantLetters[];
extern puzzle_t puzzles[];
extern s32 siLockMade;
extern data80057808_t D_80057808[];
extern Gfx *D_800578B0[];
extern Mtx *D_80057910[];
extern s32 D_80057970[][3];
extern Gfx *D_80057988[];
extern u8 *D_800579BC[];           // the pictures of the letters, by character
extern Gfx *D_800579F0[];           // D_800579F0 to D_80057A90: the display lists of the squares of each row
extern Gfx *D_80057A20[];
extern Gfx *D_80057A58[];
extern u16 *D_80057A68[];
extern Gfx *D_80057A90[];
extern Gfx *D_80057B50[][8];
extern layer_t D_80057BB0[];
extern wedgeDl_t *D_80057F08[];
extern Gfx *D_80057F24[];
extern Gfx *D_80057F34[];
extern f32 D_80057F44;
extern s32 D_80057F48;
extern view_t views[];
extern s32 D_800581F0[];
extern s32 D_800581F4;
extern s32 D_800581FC[];
extern u8 consonantOrder[];          // "RSTLNCBDMHFYKJGPQVWXZ"
extern u8 vowelOrder[];          // "EAIOU"
extern movie_t D_80058228[];
extern char D_80058488[];           // "You are the BIG winner!"
extern s32 D_800584A0[][2];         // [5], x and y of pictures 2 to 6 of the first menu
extern menuItem_t D_800584C8[];
extern image_t D_80058548[];
extern menuItem_t D_80058868[];
extern u16 *D_800588A8[][3][2];     // [3], for each contestant unk_20 and unk_24 of pictures 0, 7 and 8 of D_800588F0
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
extern u16 *D_8005A8C8[];
extern u16 *D_8005A930[];
extern image_t D_8005A998[];
extern u16 *D_8005ACE8[];
extern image_t D_8005ADD0[][7];
extern s32 D_8005B088[];
extern u16 *D_8005B118[];
extern s32 D_8005B148[];
extern s32 D_8005B170;
extern s32 D_8005B174;
extern s32 D_8005B178[];
extern image_t D_8005B1A8[];
extern image_t D_8005B2C0[];
extern image_t D_8005B310[];
extern image_t D_8005B360[];
extern image_t D_8005B4C8[];
extern u16 *D_8005B5A4[];
extern image_t D_8005B630[];
extern image_t D_8005B710[];
extern s32 D_8005BA80[];
extern image_t D_8005BAC0[];
extern letterImage_t D_8005BCC8[];
extern image_t D_8005BE00[];
extern u8 *D_8005C1E8[];
extern u8 *D_8005C33C[];
extern u8 D_8005C394[];
extern Gfx *D_8005C3A0[][2];        // [3], dl and secondDl of the obj of each contestant
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
extern camera_t openingPath[];
extern s32 memEnd;
extern s32 memStart;
extern s32 D_8006DCEC;
extern s32 D_8006DCF0;
extern s32 D_8006DCF4;
extern s32 D_8006DCF8;
extern s32 sfxCtlRom;
extern s32 sfxCtlRomEnd;
extern s32 sfxTblRom;
extern s32 D_8006DDC4;
extern long long int D_80082BC8[];  // the data of the graphics microcode at D_80034A88
extern long long int D_80083BC8[];  // aspMainDataStart
extern s32 D_80086D58;
extern ALCSeq *seqs[];
extern ALSndpConfig sndpConfig;
extern ALInstrument *sfxInst;    // the first instrument of the bank: its sounds are the sound effects
extern ALSound *curSound;
extern ALSndId *soundIds;         // [MAX_SOUNDS], -1 where no sound is allocated
extern u64 audioStack[];            // audioStack: AUDIO_STACKSIZE bytes
extern OSContStatus contStatus[];
extern OSContPad contPads[];
extern OSScMsg contEventMsg;          // the message of the controller event
extern OSThread rumbleThread;         // the rumble thread, RumbleThread
extern u64 rumbleThreadStack[];            // its stack: 0x2000 bytes
extern OSThread contThread;         // the controller thread, ControllerThread
extern u64 contThreadStack[];            // its stack: 0x2000 bytes
extern OSPfs contPfs[];          // [MAXCONTROLLERS]
extern s32 numGfxTasks;
extern u64 gameThreadStack[];            // the stack of the thread gameThread: 0x2000 bytes
extern OSThread mainThread;         // the main thread, mainproc
extern OSThread idleThread;         // the idle thread, idle
extern OSThread gameThread;         // the game thread, GameThread
extern u64 idleThreadStack[];            // the stack of the idle thread: 0x2000 bytes
extern OSMesg PiMessages[];          // [200], the messages of the PI manager
extern OSMesgQueue PiMessageQ;      // the queue of the PI manager
extern OSMesgQueue dmaMessageQ;      // where ReadRom waits for its read
extern OSMesg dmaMessageBuf;
extern OSMesgQueue contMsgQ;      // the queue of the controller events
extern OSScClient D_800B3988;
extern ALBankFile *sfxBankFile;
extern s32 openingFrame;
extern ALBankFile *seqBankFile;      // NOTE: nothing sets it
extern f32 cameraTurn[][2];         // [3], for each player what the buttons have added to roll and pitch of the camera
extern wedge_t wedges[];
extern s32 minRetraces;
extern u64 dram_stack[];            // the stack of the graphics microcode: SP_DRAM_STACK_SIZE8 bytes
extern s32 bonusTimeLeft;
extern s32 D_800B40C4;
extern obj_t objst[];
extern s32 openingFrames;
extern s32 round;
extern s32 curGfxInfo;
extern s32 D_800B61A4;
extern s32 lightDir;
extern s8 D_800B61AA[];
extern f32 D_800B61AC;
extern s8 D_800B61B0[];
extern u8 curLetter;
extern s32 solveRow;
extern u8 cpuConsonants[];          // InitCpuLetters copies consonantOrder here
extern s32 curPuzzle;
extern u64 gfxYieldBuf[];            // the yield buffer of the graphics task: 0x900 bytes
extern u8 cpuVowels[];          // InitCpuLetters copies vowelOrder here
extern s32 buttonUpFrames[][16];
extern f32 cameraUpX;
extern f32 cameraUpY;
extern f32 cameraUpZ;
extern OSMesg rumbleMsgBuf;
extern u8 blocks[][0x50];       // [70], the data blocks of the procs: AllocBlock hands them out
extern ALSeqFile *seqFile;
extern s32 roundTime;
extern s32 D_800B81E0;
extern s32 *D_800B81E4;
extern Gfx *glistp;
extern s32 soundStates[];
extern s32 memStackTop;
extern s32 D_800B8294;
extern f32 cpuSkill;
extern proc_t procst[];
extern s32 D_800B9538;
extern s32 finalSpinValue;
extern s32 jackpot;
extern u8 category[];
extern u8 board[][21];
extern u8 solveBoard[][21];
extern u8 puzzleText[][21];
extern s8 D_800B9655[];
extern u8 uncalled[];
extern OSMesgQueue gfxMsgQ;      // where the scheduler answers the graphics tasks and sends the retraces
extern s32 jackpotWon;
extern s32 D_800B96A4;
extern s32 D_800B96A8;
extern u32 retraceCount;
extern u16 buttonsPressed;
extern s32 frameRetraces;
extern s32 maxDmaBuffsUsed;
extern u32 minFrameSize;              // minFrameSize
extern s32 numRounds;
extern u8 contPattern;
extern OSSched sc;
extern u32 maxFrameSize;              // maxFrameSize
extern OSContPad playerPad;
extern ALHeap audioHeap;
extern s32 D_800B9974;
extern s32 D_800B9980;
extern s32 memStackFree;
extern s32 D_800B9988;
extern s16 *D_800B998C;
extern player_t players[];
extern OSMesgQueue D_800B9CD0;
extern s32 D_800B9CEC;
extern s32 gameOver;
extern void *D_800B9CF4;
extern s32 canSpin;
extern s32 canBuyVowel;
extern s32 canSolve;
extern s32 newFrame;
extern tile_t D_800B9D08[];
extern tile_t D_800B9E58[];
extern tile_t D_800B9FE0[];
extern tile_t D_800BA168[];
extern s32 curView;
extern s32 D_800BA2C0;
extern AMDMABuffer dmaBuffs[];     // dmaBuffs[NUM_DMA_BUFFERS]
extern OSMesgQueue audDMAMessageQ;       // audDMAMessageQ
extern OSMesgQueue siLockQ;      // holds one message: LockSi takes it, UnlockSi puts it back
extern AMDMAState dmaState;        // dmaState
extern s32 D_800BA5D4;
extern camera_t *curCamera;
extern s32 blockOwners[];
extern u64 scheduleStack[];            // the stack of the scheduler: OS_SC_STACKSIZE bytes
extern u16 numSoundsPlaying;
extern s32 D_800BC6FC;
extern OSIoMesg audDMAIOMesgBuf[];       // audDMAIOMesgBuf[NUM_DMA_MESSAGES]
extern s32 finalSpin;
extern s32 memStackDepth;
extern void *staticSegment;           // segment 1: the display lists and pictures InitGraphics loads
extern s32 D_800BCA0C;
extern s32 numObjs;
extern s32 D_800BCA14;
extern s32 memStackEnd;
extern s32 D_800BCA1C;
extern s32 D_800BCA20;
extern s32 memStackBase;
extern s32 D_800BCA28;
extern rumbleMsg_t rumbleMsg;
extern OSMesg gfxMsgBuf[];          // [8], the messages of gfxMsgQ
extern s32 D_800BCA60;
extern AMAudioMgr __am;        // __am
extern f32 wheelSpeed;
extern s32 solveCol;
extern s32 D_800BCD50;
extern s32 gameMode;
extern OSScClient gfxClient;
extern u32 frameSize;              // frameSize
extern OSMesg contMsgBuf;
extern OSMesgQueue rumbleMsgQ;      // the queue of the rumble thread
extern u64 mainThreadStack[];            // the stack of the main thread: 0x2000 bytes
extern s32 D_800BED88;
extern ALCSPlayer *seqPlayers[];
extern s32 D_800BED98;
extern u32 maxRSPCmds;              // maxRSPCmds
extern s32 curWedge;
extern s32 memStackMarks[];
extern s32 D_800BEDD8[];
extern u32 pendingGfx;
extern s32 motorOn[];
extern s32 wedgeThird;
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
extern s32 numProcs;
extern s32 D_800BEE54;
extern u16 contPressed[];
extern rumble_t rumbles[];
extern OSMesgQueue *sched_cmdQ;      // the command queue of the scheduler
extern u16 *D_800BEEA8[][8];
extern gfxInfo_t gfxInfo[];
extern s32 curPlayer;
extern s32 contReading;
extern u64 retraceTime;
extern OSMesg audDMAMessageBuf[];          // audDMAMessageBuf[NUM_DMA_MESSAGES]
extern u16 zbuffer[];            // the depth buffer
extern u16 D_803B5000[];            // D_803B5000 and D_803DA800: the two framebuffers
extern u16 D_803DA800[];
extern puzzleRange_t puzzleRanges[];  // on the cartridge, read in place

//
// functions, in address order: the unit boundaries are not known yet
//
void InitAudio( void );
void PlaySequence( s32 seqNo, s32 player );
void StopSequence( s32 player );
s32 FindFreeSound( void );
void PauseSounds( void );
void ResumeSounds( void );
s32 IsSoundStopped( s32 slot );
s32 PlaySound( s32 sound );
void StopSound( s32 slot );
void SetSoundMix( s32 slot, s32 fxMix, s32 pan, s32 vol );
void SetSoundPitch( s32 slot, f32 pitch );
void StopAllSounds( void );
s32 GetSoundCount( void );
s32 GetSeqCount( void );
void amCreateAudioMgr( ALSynConfig *c, OSPri pri, amConfig *amc );
void __amMain( void *arg );
u32 __amHandleFrameMsg( AudioInfo *info, AudioInfo *lastInfo );
void __amHandleDoneMsg( AudioInfo *info );
s32 __amDMA( s32 addr, s32 len, void *state );
ALDMAproc __amDmaNew( AMDMAState **state );
void __clearAudioDMA( void );
void ControllerThread( void *arg );
void InitControllers( void );
void ReadControllers( void );
void StartMotor( s32 cont );
void StopMotor( s32 cont );
void ResetMotor( s32 cont );
void RumbleThread( void *arg );
void ResetMotors( void );
void SetLightColor( s32 light );
void InitGraphics( void );
void func_80005700( void );
void createGfxTask( gfxInfo_t *info );
void ResetScissor( frame_t *frame );
void parse_args( s32 argstring );
void boot( void );
void idle( void *arg );
void RunFrame( void );
void mainproc( void *arg );
void GameThread( void *arg );
void ReadRom( s32 rom, void *ram, s32 size );
void InitGame( void );
void NewGame( void );
void ResetGame( void );
void StartRound( void );
void LoadPuzzle( s32 puzzle, u8 *str );
s32 CountLetter( s32 letter );
s32 IsVowel( s32 letter );
s32 CallLetter( s32 c, s32 kind );
void ShowLetter( s32 letter );
s32 CheckSolved( s32 bank );
s32 GetHiddenKinds( void );
s32 GetUncalledKinds( void );
f32 CheckPercentDone( void );
void StartSolve( void );
s32 CheckSolve( void );
void InitWheel( void );
void ClaimWedge( void );
void SetWedge( f32 degrees );
s32 GetWedgeValue( void );
void ApplyWedge( s32 final );
void ClearScores( void );
void NextPlayer( s32 newRound );
u8 *StrNCopy( u8 *dst, u8 *src, s32 n );
u8 *StrCat( u8 *dst, u8 *src );
u8 *StrCopy( u8 *dst, u8 *src );
u8 *StrChr( u8 *str, s32 c );
s32 StrLen( u8 *str );
void IntToStr( u8 *dst, s32 value );
s32 Random( s32 range );
void func_80009D08( s32 arg0 );
s32 Abs( s32 value );
void PrintNum( s32 num );
void func_80009F38( char *msg );
void PrintStr( u8 *str );
void InitProcs( void );
proc_t *GetLastProc( void );
proc_t *GetProcBefore( proc_t *proc );
proc_t *AllocProc( void );
void *AllocBlock( s32 owner );
void FreeBlocks( s32 owner );
s32 KillProc( proc_t *proc, s32 killObjs );
proc_t *CreatProc( procHandler_t handler, s32 cls );
void DoProcs( void );
void ProcPostEvent( s32 event );
proc_t *FindProc( s32 cls, s32 mask );
proc_t *FindNextProc( proc_t *proc, s32 cls, s32 mask );
void ProcPostMessage( proc_t *proc, s32 msg, s32 wake );
void ProcPostMessageClass( s32 msg, s32 cls, s32 mask, s32 wake );
s32 ProcGetMessage( proc_t *proc );
void ProcClearMessages( proc_t *proc );
void KillOtherProcs( proc_t *proc );
void KillProcClass( s32 cls, s32 mask, s32 killObjs );
void InitObjs( void );
obj_t *GetLastObj( void );
obj_t *GetObjBefore( obj_t *obj );
obj_t *AllocObj( void );
s32 FreeObj( obj_t *obj );
void FreeProcObjs( s32 owner );
obj_t *CreatObj( s32 owner, objDraw_t draw, s32 cls );
void DrawObjs( frame_t *frame );
void DrawTopObjs( frame_t *frame );
obj_t *FindObj( s32 cls, s32 mask );
obj_t *FindNextObj( obj_t *obj, s32 cls, s32 mask );
void FreeObjClass( s32 cls, s32 mask );
void InitMemStack( void );
void *mem_stack( s32 size );
void AlignMemStack( s32 align );
void *func_8000B924( s32 size );
s32 PushMemStack( void );
void PopMemStack( s32 count );
void InitSiLock( void );
void LockSi( void );
void UnlockSi( void );
void func_8000BBA8( void );
struct procResult_s func_8000BC64( proc_t *proc );
void func_8000BE6C( void );
struct procResult_s func_8000BEA8( proc_t *proc );
struct procResult_s func_8000C310( proc_t *proc );
struct procResult_s func_8000C50C( proc_t *proc );
struct procResult_s func_8000C6C4( proc_t *proc );
struct procResult_s func_8000C8A8( proc_t *proc );
void func_8000CB58( obj_t *obj, frame_t *frame );
void func_8000D400( obj_t *obj, frame_t *frame );
void func_8000D6D8( obj_t *obj, frame_t *frame );
void func_8000D8B8( obj_t *obj, frame_t *frame );
void func_8000DCA0( obj_t *obj, frame_t *frame );
void func_8000DF2C( obj_t *obj, frame_t *frame );
struct procResult_s LogoProc( proc_t *proc );
void StartLogos( void );
void func_8000E738( void );
void RestartOpening( void );
void StartOpening( void );
struct procResult_s DemoProc( proc_t *proc );
void func_8000EE50( s32 arg0, s32 arg1 );
void StartDemo( void );
struct procResult_s WheelPullProc( proc_t *proc );
struct procResult_s PointerProc( proc_t *proc );
struct procResult_s func_8000F740( proc_t *proc );
struct procResult_s WheelStopProc( proc_t *proc );
struct procResult_s TurnWheel( proc_t *proc );
struct procResult_s WheelSpinProc( proc_t *proc );
struct procResult_s func_8000FFE0( proc_t *proc );
struct procResult_s func_800101F4( proc_t *proc );
struct procResult_s func_800103B4( proc_t *proc );
struct procResult_s LightLetterProc( proc_t *proc );
void TurnSquares( s32 col );
struct procResult_s LightTextProc( proc_t *proc );
s32 FindHiddenSquare( s32 row, s32 col, s32 dir );
void SetSquareBlink( s32 row, s32 col, s32 blink );
void SetSquareLetter( s32 row, s32 col, u8 letter );
void NextSolveSquare( void );
void PrevSolveSquare( void );
void ResetSquares( void );
void RevealPuzzle( void );
void GreyHiddenSquares( void );
struct procResult_s CursorProc( proc_t *proc );
void DrawPointer( obj_t *obj, frame_t *frame );
s32 GetSquareColor( tile_t *arg0 );
void DrawSquares( tile_t *tiles, s32 count, s32 arg2 );
void DrawBoard( obj_t *obj, frame_t *frame );
void LightPlayer( s32 player );
void UnlightPlayers( void );
s32 GetLayerColor( layer_t *layer );
void SetScoreDigits( s32 total );
void DrawScores( obj_t *obj, frame_t *frame );
void func_80014208( obj_t *obj, frame_t *frame );
void func_800144F0( obj_t *obj, frame_t *frame );
void func_80014768( obj_t *obj, frame_t *frame );
void func_80014A5C( obj_t *obj, frame_t *frame );
void DrawWheel( obj_t *obj, frame_t *frame );
void func_800153C4( obj_t *obj, frame_t *frame );
obj_t *MakeObj( proc_t *proc, Gfx *dl, objDraw_t draw, s32 cls );
void InitSquares( Gfx **dls, tile_t *tiles, s32 row, s32 count );
void InitBoard( void );
void ClearSquares( Gfx **dls, tile_t *tiles, s32 row, s32 count );
void StartBoardLights( void );
void func_80016098( void );
void ResetBoard( void );
void InitStage( void );
s32 func_80016638( void );
s32 func_800166C0( void );
struct procResult_s CameraPathProc( proc_t *proc );
void SetView( obj_t *obj, s32 view );
void SetCameraView( s32 view );
struct procResult_s CameraProc( proc_t *proc );
void DrawCamera( obj_t *obj, frame_t *frame );
void InitCamera( proc_t *proc );
void CreateCamera( void );
s32 LoseTurn( void );
void NextTurn( void );
s32 func_80017728( void );
void NextRound( void );
void FindWinner( void );
struct procResult_s AdjustCameraProc( proc_t *proc );
void SetGameView( s32 view, s32 arg1 );
struct procResult_s RoundOverProc( proc_t *proc );
struct procResult_s WinnerProc( proc_t *proc );
struct procResult_s SpinProc( proc_t *proc );
struct procResult_s BuyVowelProc( proc_t *proc );
struct procResult_s SolveProc( proc_t *proc );
struct procResult_s FinalSpinTurnProc( proc_t *proc );
struct procResult_s PlayerTurnProc( proc_t *proc );
void AddPlayer( s32 player );
void InitPlayers( void );
void InitCpuLetters( void );
void RemoveCalledLetters( u8 *letters );
s32 PickMissLetter( u8 *letters );
s32 PickHitLetter( u8 *letters );
s32 CpuPickConsonant( f32 skill, proc_t *proc );
s32 CpuPickVowel( f32 skill );
void CpuChooseAction( proc_t *proc );
struct procResult_s CpuSpinProc( proc_t *proc );
struct procResult_s CpuBuyVowelProc( proc_t *proc );
struct procResult_s CpuSolveProc( proc_t *proc );
struct procResult_s CpuFinalSpinTurnProc( proc_t *proc );
struct procResult_s CpuTurnProc( proc_t *proc );
void AddDemoCpu( s32 player );
void AddCpu( s32 player );
void func_8001D440( obj_t *obj, frame_t *frame );
void func_8001DAF0( obj_t *obj, frame_t *frame );
void func_8001ED48( u16 *arg0 );
void func_8001EFF0( obj_t *obj, frame_t *frame );
void func_80020150( obj_t *obj, frame_t *frame );
void func_800202A0( u16 *arg0 );
void func_800206C8( u16 *arg0 );
void func_80020C98( u16 *arg0 );
void func_80021090( void *arg0 );
obj_t *func_800211E4( proc_t *proc, char *arg1, f32 x, f32 y, s32 arg4 );
void func_800212C0( proc_t *proc );
void func_800213CC( proc_t *proc );
struct procResult_s func_80021548( proc_t *proc );
struct procResult_s func_80021744( proc_t *proc );
char *func_80021908( s32 arg0 );
void func_800219B8( s32 arg0, s32 arg1, s32 arg2, s32 arg3 );
void func_80021B04( s32 arg0, s32 arg1 );
void func_80021B4C( s32 arg0, s32 arg1, s16 *arg2, s32 *arg3 );
void func_80021C8C( s32 arg0, s32 *arg1, obj_t *arg2, s32 arg3, s32 arg4 );
void func_80021E28( void );
void func_80021E88( obj_t *obj, frame_t *frame );
void func_8002208C( obj_t *obj, frame_t *frame );
void func_80022218( obj_t *obj, frame_t *frame );
void func_800223A4( obj_t *obj, frame_t *frame );
void func_80022530( obj_t *obj, frame_t *frame );
void func_800226BC( image_t *images, s32 count, s32 arg2 );
void func_80022784( proc_t *proc, image_t *images, menuItem_t *item, s32 arg3 );
void func_800229D0( proc_t *proc, image_t *images, menuItem_t *items, s32 count );
void func_80022BC8( proc_t *proc, image_t *images, menuItem_t *items, s32 count );
void func_80022DC0( proc_t *proc, image_t *images, menuItem_t *item, s32 arg3 );
void func_80022FE0( proc_t *proc, image_t *images, menuItem_t *item, s32 arg3 );
void func_80023200( void );
struct procResult_s func_800232AC( proc_t *proc );
void func_80023B44( void );
struct procResult_s func_80023CA4( proc_t *proc );
struct procResult_s func_80024370( proc_t *proc );
struct procResult_s func_80024868( proc_t *proc );
void func_80024D60( s32 arg0 );
void func_8002500C( void );
struct procResult_s func_80025150( proc_t *proc );
void func_800258BC( void );
void func_80025FA8( void );
void func_800263DC( void );
void func_80026800( void );
void func_80026DEC( void );
void func_80026E50( void );
void func_80026EB4( void );
void func_80026FD4( void );
obj_t *func_80027218( proc_t *proc, Gfx *arg1, objDraw_t draw, s32 arg3 );
u16 *func_8002731C( image_t *image, s32 arg1 );
void func_8002741C( image_t *image, s32 arg1, s32 arg2, s32 arg3 );
void func_800278A8( image_t *image, s32 arg1 );
void func_800278F0( obj_t *obj, frame_t *frame );
void func_80027F3C( obj_t *obj, frame_t *frame );
void func_80028064( obj_t *obj, frame_t *frame );
void func_80028194( obj_t *obj, frame_t *frame );
void func_8002842C( obj_t *obj, frame_t *frame );
void func_80028554( obj_t *obj, frame_t *frame );
void func_8002867C( s32 arg0, s32 arg1 );
void func_800287A4( obj_t *obj, frame_t *frame );
void func_800288CC( obj_t *obj, frame_t *frame );
void func_800289F4( obj_t *obj, frame_t *frame );
void func_80028B1C( obj_t *obj, frame_t *frame );
void func_80028C4C( proc_t *proc );
void func_80028CC4( void );
void func_80028D3C( obj_t *obj, frame_t *frame );
struct procResult_s func_80029098( proc_t *proc );
void func_80029440( void );
void func_80029974( s32 arg0 );
void func_80029BFC( s32 arg0 );
struct procResult_s func_80029C98( proc_t *proc );
void func_8002A014( void );
void func_8002A538( void );
void MoveCursorLeft( proc_t *proc, s32 arg1 );
void MoveCursorRight( proc_t *proc, s32 arg1, s32 arg2 );
void MoveCursorUp( proc_t *proc );
void MoveCursorDown( proc_t *proc );
void func_8002AFDC( void );
void func_8002B054( void );
struct procResult_s func_8002B094( proc_t *proc );
struct procResult_s func_8002B318( proc_t *proc );
struct procResult_s func_8002B730( proc_t *proc );
struct procResult_s func_8002B904( proc_t *proc );
struct procResult_s func_8002BA44( proc_t *proc );
struct procResult_s func_8002BCF4( proc_t *proc );
struct procResult_s func_8002BE84( proc_t *proc );
struct procResult_s func_8002C094( proc_t *proc );
void func_8002CAB4( void );
struct procResult_s StatusProc( proc_t *proc );
void InitLetterCursor( proc_t *proc );
struct procResult_s LetterPickProc( proc_t *proc );
s32 CountSolveBlanks( void );
proc_t *GetCursorProc( void );
struct procResult_s SolvePuzzleProc( proc_t *proc );
void StartLetterPick( void );
void StartCpuLetterPick( s32 letter );
void StartSolvePuzzle( void );
void StartStatus( void );
void func_8002EDC0( void );
void StartBonusRound( void );
struct procResult_s FinalSpinProc( proc_t *proc );
struct procResult_s RoundTimerProc( proc_t *proc );
struct procResult_s DemoTimerProc( proc_t *proc );
struct procResult_s SolveTimerProc( proc_t *proc );
struct procResult_s func_8002FB60( proc_t *proc );
void func_8002FCD8( void );
void func_8002FD14( void );
void StartSolveTimer( void );
void ResetSolveTimer( void );
void StartRoundTimer( void );
void StartDemoTimer( void );
void func_8002FEB0( obj_t *obj, frame_t *frame );
void func_80030490( obj_t *obj, frame_t *frame );
void func_80030B5C( obj_t *obj, frame_t *frame );
void func_80031340( s16 *arg0, s32 arg1 );
void func_8003143C( s16 *arg0, s32 arg1 );
struct procResult_s func_800315FC( proc_t *proc );
struct procResult_s func_80031A54( proc_t *proc );
void func_800323C4( s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4 );
void func_800325D0( s32 arg0, s32 arg1 );
void func_80032858( void );
proc_t *func_8003288C( s32 arg0, s32 arg1 );
void func_80032AD4( s32 arg0 );
void func_80032B10( void );
void func_80032B80( void );
void func_80032BF0( void );
s32 func_80033150( s32 arg0, s32 arg1, s32 arg2 );
void func_80033334( void );
void func_800334E4( void );
void func_800335D0( void );
struct procResult_s func_80033688( proc_t *proc );
void func_800339E8( void );
struct procResult_s func_80033A28( proc_t *proc );
void func_80033CBC( void );
void func_80033CF8( obj_t *obj, frame_t *frame );
struct procResult_s func_80034028( proc_t *proc );
void func_800343F8( s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6,
                    s32 arg7 );
struct procResult_s func_800345E8( proc_t *proc );

void func_80034950( void );
void func_8009CEC0( char *movie, s32 gamma );
s32 func_8009D244( void );
void func_800A4E58( void *stream );

#endif // WOF_H
