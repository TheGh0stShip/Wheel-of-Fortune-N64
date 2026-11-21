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
    /* 0x04C80 */ Mtx hubRotate;
    /* 0x04CC0 */ Gfx glist[3048];
    /* 0x0AC00 */ s16 clipPictures[6][64 * 64];    // six pictures of 64 by 64
    /* 0x16C00 */ s16 vannaPicture[64 * 96];
    /* 0x19C00 */ s16 moviePicture[0x2400];        // each screen lays out its own pictures here
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
    /* 0x34 */ s32              creatZero1;     // CreatProc zeroes it and creatZero2; nothing reads them
    /* 0x38 */ s32              creatZero2;
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
    /* 0x04 */ s32 slot;   // as anim_t.slot: VannaAnimProc reads it, nothing sets it
    /* 0x08 */ s16 *pictures;         // its pictures: count of the clip_t
    /* 0x0C */ s32 anim;
    /* 0x10 */ s32 frame;
    /* 0x14 */ s32 frameTime;      // retraces a picture shows
    /* 0x18 */ s32 count;
    /* 0x1C */ s32 loop;
    /* 0x20 */ s32 mirror;
    /* 0x24 */ s32 step;
    /* 0x28 */ s32 timer;
} vannaAnim_t;    // size 0x2C

// A picture DrawImageAt draws: where it goes and how big it is. The tables of them start at
// mainMenu1Images.
typedef struct {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
    /* 0x08 */ s32 width;
    /* 0x0C */ s32 height;
    /* 0x10 */ s32 flash;          // 0: lit, 1: flashing, 2: dim
    /* 0x14 */ s32 flashFrames;    // the frames of one flash
    /* 0x18 */ s32 flashLit;       // of those, the frames the lit texture shows
    /* 0x1C */ s32 flashLeft;      // the frames left of this flash
    /* 0x20 */ u16 *texture;     // the two textures GetImageTexture chooses from; 0: none
    /* 0x24 */ u16 *dimTexture;
} image_t;    // size 0x28


// One of the MPEG movies on the cartridge: movies[38]. LoadMovie loads one.
typedef struct {
    /* 0x00 */ s32 rom;         // where it is on the cartridge
    /* 0x04 */ s32 sound;      // if above 0, the proc that plays the movie puts it in movieSound
    /* 0x08 */ s32 *size;       // points at its size in bytes, less one
    /* 0x0C */ s32 gamma;      // 1, 2 or 3: what mpegStart is told about it
} movie_t;    // size 0x10

// One line of a menu: a label, and options of which one is chosen. A line holds numbers of
// pictures in the image_t table of its menu. The menus are mainMenu1[4], contestantMenu[2],
// mainMenu3[4], skillMenu[2] and roundsMenu[2].
typedef struct {
    /* 0x00 */ s32  selectable;                     // 0: the cursor passes the line by
    /* 0x04 */ s32  label;                     // the first picture of the label
    /* 0x08 */ s32  labelCount;                     // how many pictures the label has
    /* 0x0C */ s32  options;                     // the first picture of the first option
    /* 0x10 */ s32  rows;                       // how many options
    /* 0x14 */ s32  cols;                       // how many pictures an option has
    /* 0x18 */ s32  sel;                        // the chosen option
    /* 0x1C */ void ( *callback )( s32 line );  // called when the cursor comes to the line
} menuItem_t;    // size 0x20

// The data of the procs that run a menu (handlers MainMenu1Proc, ContestantMenuProc, SkillMenuProc,
// RoundsMenuProc and MainMenu3Proc), and of the four helpers that move its cursor. The name is
// from the ROM message "MainMenu1 Proc: button press invalid".
typedef struct {
    /* 0x00 */ u8  unk_00[0x4];
    /* 0x04 */ s32 sel;         // the chosen option of the line the cursor is on
    /* 0x08 */ s32 index;       // the line the cursor is on
    /* 0x0C */ s32 delay;       // frames until the stick moves the cursor again
} mainMenu_t;    // size 0x10
// The picture of a letter of the alphabet as BonusRoundProc shows the letter chosen:
// bonusLetterImages[26].
typedef struct {
    /* 0x00 */ u16 *texture;     // what texture of the image_t becomes
    /* 0x04 */ s32 width;
    /* 0x08 */ s32 height;
} letterImage_t;    // size 0xC

// A run of pictures that the MPEG player decodes into memory once, to be shown one at a time:
// what a contestant or Vanna does. contestantClips[6][2] and contestantMovies[6][2] are those of the six
// contestants, menuClips[6] those shown where a contestant is chosen, vannaClips[6] those of
// Vanna.
typedef struct {
    /* 0x00 */ s32 width;
    /* 0x04 */ s32 height;
    /* 0x08 */ s32 count;       // how many pictures; 0: there is no such run
    /* 0x0C */ s32 frameTime;   // retraces a picture shows: VannaAnimProc uses it, AnimProc takes 4
    /* 0x10 */ s32 loop;
    /* 0x14 */ s32 mirror;
    /* 0x18 */ s16 *pictures;     // the pictures, once they are decoded
    /* 0x1C */ s32 movie;       // its number in movies
    /* 0x20 */ s32 *mask;     // what curMask is while it is decoded
} clip_t;    // size 0x24

// three coordinates: where InitMenuAnim puts a contestant's obj
typedef struct {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
    /* 0x08 */ s32 z;
} vec_t;    // size 0xC

// The sounds of one of the six contestants a player can be: voices[6]. SetContestantSounds copies
// them into letterSounds to winSound of the player_t, in this order.
typedef struct {
    /* 0x00 */ s32 letters;      // the first of 26 sounds: the letters, as the contestant calls them
    /* 0x04 */ s32 spinSound;
    /* 0x08 */ s32 buyVowelSound;
    /* 0x0C */ s32 solveSound;
    /* 0x10 */ s32 freeSpinSound;
    /* 0x14 */ s32 winSound;      // -1: the contestant has none
} voice_t;    // size 0x18

// One of the three contestants: players[3].
typedef struct {
    /* 0x000 */ s32 score;
    /* 0x004 */ s32 total;
    /* 0x008 */ s32 freeSpin;
    /* 0x00C */ s32 hasPrize;
    /* 0x010 */ s32 roundStartZero;   // StartRound zeroes it; nothing reads it
    /* 0x014 */ s32 controller;
    /* 0x018 */ s32 contestant;
    /* 0x01C */ u8 name[0x14];
    /* 0x030 */ u8 scoreStrings[10][0x14];   // ClearScores sets each to "0"; nothing reads them
    /* 0x0F8 */ s32 prize;
    /* 0x0FC */ s32 letterSounds;
    /* 0x100 */ s32 spinSound;
    /* 0x104 */ s32 buyVowelSound;
    /* 0x108 */ s32 solveSound;
    /* 0x10C */ s32 freeSpinSound;
    /* 0x110 */ s32 winSound;
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
    /* 0x00 */ s32 value;
    /* 0x04 */ s8 name[0x14];
    /* 0x18 */ s32 special;      // 1 on 10000, FREE SPIN, JACKPOT until claimed; unread
    /* 0x1C */ s32 claimed;
} wedge_t;    // size 0x20

// The display lists of one wedge of the wheel. wedgeDls[7] points at the 24 of each kind of
// round.
typedef struct {
    /* 0x00 */ Gfx *dl;
    /* 0x04 */ Gfx *claimedDl;     // if not 0, drawn in its place once the wedge is claimed
} wedgeDl_t;    // size 0x8

// One puzzle of the built-in list: puzzles[].
typedef struct {
    /* 0x00 */ s32 rom;
    /* 0x04 */ u8  *category;     // its category, which LoadPuzzle copies into category
    /* 0x08 */ s32 used;
} puzzle_t;    // size 0xC

// The entries of titleLetters[]: the display list and the matrix of one of the objs StartOpening
// makes, drawn by DrawOpeningPiece.
typedef struct {
    /* 0x00 */ Gfx *dl;
    /* 0x04 */ Mtx *mtx;
    /* 0x08 */ f32 spread;
} titleLetter_t;    // size 0xC

// The entries of scorePanels[]. GetLayerColor gives the colour an entry is drawn in: color, or
// blinkColor for the first half of each blink while blink is set.
typedef struct {
    /* 0x00 */ Gfx *dl;     // its display list
    /* 0x04 */ s32 blink;      // not 0: it blinks
    /* 0x08 */ s32 blinkFrames;      // the frames one blink takes
    /* 0x0C */ s32 blinkLeft;      // the frames left of this blink
    /* 0x10 */ s32 color;
    /* 0x14 */ s32 blinkColor;
} layer_t;    // size 0x18

// One square of the puzzle board. The four rows are topRow[12], secondRow[14],
// thirdRow[14] and bottomRow[12].
typedef struct {
    /* 0x00 */ Gfx *dl;     // its display list
    /* 0x04 */ u8  *image;     // the picture it shows
    /* 0x08 */ u8  *letterImage;     // the picture of its letter, shown once the square is turned
    /* 0x0C */ s32 blink;      // not 0: it blinks
    /* 0x10 */ s32 blinkFrames;      // the frames one blink takes
    /* 0x14 */ s32 blinkLeft;      // the frames left of this blink
    /* 0x18 */ s32 color;      // its colour
} tile_t;    // size 0x1C

// the data of the proc whose handler is OpeningProc
typedef struct {
    /* 0x00 */ obj_t *obj;
    /* 0x04 */ s32 music;
    /* 0x08 */ u8 unk_08[0x4];
    /* 0x0C */ f32 x;
    /* 0x10 */ f32 y;
    /* 0x14 */ f32 z;
} opening_t;    // size 0x18

// the data of the proc whose handler is OpeningWheelProc
typedef struct {
    /* 0x00 */ obj_t *obj;
} openingWheel_t;    // size 0x4

// the data of the proc whose handler is OpeningWedgeProc
typedef struct {
    /* 0x00 */ obj_t *obj;
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ s32 index;
} openingWedge_t;    // size 0xC

// the data of the proc whose handler is TitleLetterProc
typedef struct {
    /* 0x00 */ obj_t *pos;
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ s32 index;
} titleLetterProc_t;    // size 0xC

// the data of the proc whose handler is DebugCameraProc
typedef struct {
    /* 0x00 */ obj_t *cam;
} debugCamera_t;    // size 0x4

// the data of the proc whose handler is WheelPullProc
typedef struct {
    /* 0x00 */ u8 unk_00[0xC];
    /* 0x0C */ f32 restPitch;
} wheelPull_t;    // size 0x10

// the data of the proc whose handler is PointerProc, created by InitStage 
typedef struct {
    /* 0x00 */ obj_t *actor;
    /* 0x04 */ f32 offset;
    /* 0x08 */ s32 swing;
} pointer_t;    // size 0xC

// the data of the proc whose handler is WheelStopProc, created by TurnWheel
typedef struct {
    /* 0x00 */ obj_t *obj;   // NOTE: no obj is made for this proc; the handler reads it all the same
    /* 0x04 */ s32 was3500;     // WheelStopProc sets it when the wedge is worth 3500; unread
} wheelStop_t;    // size 0x8

// The data of the proc whose handler is WheelSpinProc, which ends each frame in TurnWheel
// on the same data. SpinProc, CpuSpinProc and FinalSpinProc create it and put the obj
// of class 0x401 in wheel.
typedef struct {
    /* 0x00 */ obj_t *wheel;
    /* 0x04 */ s32 spinStartZero;   // WheelSpinProc zeroes it as the spin starts; unread
    /* 0x08 */ u8 unk_08[0x4];
    /* 0x0C */ f32 speed;
    /* 0x10 */ f32 lastSpeed;
} wheelSpin_t;    // size 0x14

// the data of the proc whose handler is BoardLightsProc
typedef struct {
    /* 0x00 */ obj_t *obj;
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ s32 frames;
} boardLights_t;    // size 0xC

// the data of the proc whose handler is WheelLightsProc
typedef struct {
    /* 0x00 */ obj_t *obj;
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ s32 frames;
} wheelLights_t;    // size 0xC

// the data of the proc whose handler is BaseLightsProc
typedef struct {
    /* 0x00 */ obj_t *obj;
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ s32 frames;
} baseLights_t;    // size 0xC

// the data of the proc whose handler is LightLetterProc
typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 row;
    /* 0x08 */ s32 col;
    /* 0x0C */ s32 vannaStarted;   // set once SetVannaAnim(0) has started her walk
    /* 0x10 */ u8 letter;
} lightLetter_t;    // size 0x14

// the data of the proc whose handler is LightTextProc, created by BonusRoundProc
typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 row;
    /* 0x08 */ s32 col;
    /* 0x0C */ u8 unk_0C[0x8];
    /* 0x14 */ u8 *text;
} lightText_t;    // size 0x18

// the data of the proc whose handler is CameraPathProc, created by SetView
typedef struct {
    /* 0x00 */ obj_t *obj;   // NOTE: no obj is made for this proc; the handler reads it all the same
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ camera_t *path;    // the move it plays
    /* 0x0C */ s32 frame;          // the frame it is at
    /* 0x10 */ s32 count;          // how many frames the move has
} cameraPath_t;    // size 0x14

// the data of the proc whose handler is AdjustCameraProc, created by SetGameView
typedef struct {
    /* 0x00 */ u8  unk_00[0x4];
    /* 0x04 */ s32 player;      // the player whose turn it was made in
} adjustCamera_t;    // size 0x8

// The data of a player proc: the proc of a turn, whose handler is PlayerTurnProc for a person
// and CpuTurnProc for the machine, and the procs a turn makes for its steps, to which it
// copies player, and from CpuTurnProc skill as well, through this struct: RoundOverProc,
// SpinProc, BuyVowelProc, SolveProc, FinalSpinTurnProc, CpuSpinProc, CpuBuyVowelProc,
// CpuSolveProc and CpuFinalSpinTurnProc. RoundOverProc is made by both kinds of turn. The name is
// from the ROM message "Status Proc: player proc does not exist", which StatusProc prints
// when no proc of this class answers.
typedef struct {
    /* 0x00 */ u8  unk_00[0x4];
    /* 0x04 */ s32 player;      // the contestant: 0, 1 or 2
    /* 0x08 */ u8  unk_08[0x4];
    /* 0x0C */ f32 skill;
} playerProc_t;    // size 0x10

// the data of the proc whose handler is ClipProc, created by PlayClip 
typedef struct {
    /* 0x00 */ obj_t *obj;
    /* 0x04 */ u8 unk_04[0xC];
    /* 0x10 */ s32 slot;
    /* 0x14 */ u8 unk_14[0xC];
    /* 0x20 */ s32 event;
    /* 0x24 */ s32 sound;
} clipPlay_t;    // size 0x28

// the data of the proc whose handler is CategoryProc
typedef struct {
    /* 0x00 */ obj_t *obj;
    /* 0x04 */ s32 index;
} categoryShow_t;    // size 0x8

// the data of the proc whose handler is JackpotRollProc
typedef struct {
    /* 0x00 */ u8 unk_00[0x10];
    /* 0x10 */ s32 step;
} jackpotRoll_t;    // size 0x14

// the data of the proc whose handler is CreditsProc
typedef struct {
    /* 0x00 */ u8 unk_00[0x8];
    /* 0x08 */ s32 step;
} credits_t;    // size 0xC


// The data of the procs that time something out: handlers RoundTimerProc, DemoTimerProc,
// SolveTimerProc and FreeSpinTimerProc. The four are procs of one class (0x07) that keep the same
// thing in the same place and share no helper; the ROM calls the third the "Solve Timer Proc"
// (in ResetSolveTimer), which is where the name is from.
typedef struct {
    /* 0x00 */ u8  unk_00[0x4];
    /* 0x04 */ s32 start;       // when it was started or reset, in seconds since the boot
} timer_t;    // size 0x8

// the data of the proc whose handler is ConfettiBurstProc
typedef struct {
    /* 0x00 */ u8  unk_00[0x4];
    /* 0x04 */ s32 countdown;      // counts down from 10, a step a frame
} confettiBurst_t;    // size 0x8

// the data of the proc whose handler is ApplauseProc
typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 played;
    /* 0x08 */ s32 startZero;   // ApplauseProc zeroes it on its first run; unread
} applauseProc_t;    // size 0xC

// The data of the procs that move a cursor over the letters: handlers StatusProc,
// LetterPickProc and SolvePuzzleProc, and the helpers they share.
typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 index;
    /* 0x08 */ u8 unk_08[0x4];
    /* 0x0C */ s32 delay;
} cursor_t;    // size 0x10

// the data of the proc whose handler is MovieProc, created by PlayMovie
typedef struct {
    /* 0x00 */ obj_t *obj;
    /* 0x04 */ u8 unk_04[0x1C];
    /* 0x20 */ s32 event;
    /* 0x24 */ s32 sound;
} moviePlay_t;    // size 0x28

// The data of a contestant animation proc (handler AnimProc), which InitAnim creates: the
// name is from the ROM messages "InitAnim: ..." in InitMenuAnim and InitAnim.
typedef struct {
    /* 0x00 */ obj_t *obj;
    /* 0x04 */ s32 slot;
    /* 0x08 */ s16 *pictures;         // its pictures: count of the clip_t
    /* 0x0C */ u8 unk_0C[0x4];
    /* 0x10 */ s32 frame;
    /* 0x14 */ u8 unk_14[0x4];
    /* 0x18 */ s32 count;
    /* 0x1C */ s32 loop;
    /* 0x20 */ u8 unk_20[0x4];
    /* 0x24 */ s32 step;
    /* 0x28 */ s32 timer;
} anim_t;    // size 0x2C

// the data of the proc whose handler is ConfettiProc, created by AddConfetti
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
} confetti_t;    // size 0x24

// The data block of a proc (data): one of the 0x50-byte blocks of blocks, holding the
// struct of its kind of proc. A proc that has an obj keeps it in the first word: CreatProc's
// callers that make the obj (MakeObj, MakeScreenObj) store it there for every kind.
// guess: a union, which the bytes do not tell from a cast at each use.
typedef union procData_u {
    obj_t           *obj;
    vannaAnim_t     vannaAnim;
    mainMenu_t      mainMenu;
    opening_t  opening;
    openingWheel_t  openingWheel;
    openingWedge_t  openingWedge;
    titleLetterProc_t  titleLetterProc;
    debugCamera_t  debugCamera;
    wheelPull_t  wheelPull;
    pointer_t  pointer;
    wheelStop_t  wheelStop;
    wheelSpin_t  wheelSpin;
    boardLights_t  boardLights;
    wheelLights_t  wheelLights;
    baseLights_t  baseLights;
    lightLetter_t  lightLetter;
    lightText_t  lightText;
    cameraPath_t  cameraPath;
    adjustCamera_t  adjustCamera;
    playerProc_t    playerProc;
    clipPlay_t  clipPlay;
    categoryShow_t  categoryShow;
    jackpotRoll_t  jackpotRoll;
    credits_t  credits;
    timer_t         timer;
    confettiBurst_t  confettiBurst;
    applauseProc_t  applauseProc;
    cursor_t        cursor;
    moviePlay_t  moviePlay;
    anim_t          anim;
    confetti_t  confetti;
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
extern char noContestantObjMsg[];   // "InitAnim: cannot find contestant obj", in PlayContestantClip

//
// globals, in address order
//
extern long long int gfxUcodeText[];  // the text of the graphics microcode (asm/sdk/ucode_80034A88.s)
extern ALSndPlayer *sndPlayer;
extern s32 reverbParams[];            // the parameters of the custom reverb
extern u32 audFrameCt;              // audFrameCt
extern u32 nextDMA;              // nextDMA
extern u32 curAcmdList;              // curAcmdList
extern Lights7 sceneLights;          // the lights of every scene: DrawCamera sets the first six
extern s32 firstframe;              // guess: the demos' firstframe; rdpstateinit_dl goes once
extern s32 vFlag;                   // set by parse_args for the -v switch; nothing reads it
extern s32 debugflag;
extern s32 sFlag;                   // set by parse_args for the -s switch; nothing reads it
extern s32 lFlag;                   // set by parse_args for the -l switch; nothing reads it
extern s32 wheelStartAngles[];
extern s32 firstRoundWedges[];
extern s32 secondRoundWedges[];
extern s32 jackpotRoundWedges[];
extern s32 laterRoundWedges[];
extern u8 alphabet[];          // "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
extern s8 vowelLetters[];
extern s8 consonantLetters[];
extern puzzle_t puzzles[];
extern char *procEventNames[];       // the proc events by name: a debug table no function reads
extern s32 siLockMade;
extern titleLetter_t titleLetters[];
extern Gfx *openingWedgeDls[];
extern Mtx *openingWedgeMtxs[];
extern s32 logoTiles[][3];
extern Gfx *letterBoardDls[];       // [26] the letter board's letters, A to Z (see letterPictures)
extern u8 *letterPictures[];           // the pictures of the letters, by character
extern Gfx *topRowDls[];           // topRowDls to bottomRowDls: the display lists of the squares of each row
extern Gfx *secondRowDls[];
extern Gfx *thirdRowDls[];
extern u16 *scoreDigitPictures[];
extern Gfx *bottomRowDls[];
extern Gfx *scorePanelDigitDls[][8]; // [3], the 8 digit quads of each score on stage
extern layer_t scorePanels[];
extern s32 D_80057BF8[];          // four segment addresses no instruction names
extern wedgeDl_t firstRoundWedgeDls[]; // the wedges of each kind of round, as wedgeDls takes them
extern wedgeDl_t secondRoundWedgeDls[];
extern wedgeDl_t jackpotRoundWedgeDls[];
extern wedgeDl_t laterRoundWedgeDls[];
extern wedgeDl_t *wedgeDls[];
extern Gfx *backdropDls[];
extern Gfx *backdropOverlays[];
extern f32 pullScale;
extern s32 minSpinSpeed;
extern view_t views[];
extern s32 pointerAngles[];
extern s32 playerViews[];
extern u8 consonantOrder[];          // "RSTLNCBDMHFYKJGPQVWXZ"
extern u8 vowelOrder[];          // "EAIOU"
extern movie_t movies[];
extern char winnerText[];           // "You are the BIG winner!"
extern s32 controllerLabelPos[][2];         // [5], x and y of pictures 2 to 6 of the first menu
extern menuItem_t mainMenu1[];
extern image_t mainMenu1Images[];
extern menuItem_t contestantMenu[];
extern u16 *playerMenuTextures[][3][2];     // [3], for each contestant texture and dimTexture of pictures 0, 7 and 8 of contestantMenuImages
extern image_t contestantMenuImages[];
extern menuItem_t mainMenu3[];
extern image_t mainMenu3Images[];
extern menuItem_t skillMenu[];
extern image_t skillMenuImages[];
extern menuItem_t roundsMenu[];
extern image_t roundsMenuImages[];
extern image_t marqueeImages[];
extern vec_t frontContestantPos;
extern vec_t contestantPos[];
extern voice_t voices[];
extern vec_t playerPos[];
extern u8 defaultNames[][10];
extern image_t playerStatusImages[][2];
extern image_t prizeImages[];       // [3] the prize token of each player, shown while hasPrize
extern image_t bootScreenImages[];
extern image_t noControllerImages[];
extern image_t freeSpinImages[];    // [3] the free spin token of each player, shown while freeSpin
extern image_t actionImages[];
extern u16 *calledLetterTextures[];
extern u16 *letterTextures[];
extern image_t letterImages[];
extern u16 *statusDigitTextures[];
extern image_t statusScoreImages[][7];
extern u16 *bigDigitTextures[];
extern s32 bigDigitAdvances[];
extern s32 dollarAdvance;           // read as bigDigitAdvances[10], the $ glyph's
extern s32 commaAdvance;            // bigDigitAdvances[11]: the advance of the , glyph
extern s32 bigDigitWidths[];
extern image_t bonusPrizeImages[];  // [7] $25,000 in big digits
extern image_t bonusTimerImages[];
extern image_t retraceImages[];
extern image_t rollingNumberImages[];
extern image_t bigNumberImages[];
extern u16 *categoryLetterTextures[];
extern image_t jackpotSignImages[]; // [3] the JACKPOT sign over the jackpot in round 2
extern image_t categoryImages[];
extern s32 categoryWheelFrames[];   // [16] a small wheel turning, 24 by 24
extern image_t pressStartImages[];  // [13] PRESS START in the category's letters
extern letterImage_t bonusLetterImages[];
extern image_t bonusLetterSlots[];
extern u8 *creditsText[];
extern u8 *creditsTitles[];
extern u8 givenLetters[];
extern Gfx *contestantDls[][2];        // [3], dl and secondDl of the obj of each contestant
extern clip_t contestantClips[][2];
extern clip_t contestantMovies[][2];
extern clip_t menuClips[];
extern clip_t vannaClips[];
extern s32 vannaWalkOffsets[];      // x offsets of animation 0, by picture
extern s32 vannaTurnOffsets[];      // x of animation 3, by picture: 4 with the next
extern s32 columnLeftEdges[];       // read as [i] = columnRightEdges[i - 1]
extern s32 columnRightEdges[];      // [15] the right edges of the board's columns in vannaX, from 0
extern s32 confettiTextures[];
extern f32 confettiGravity;
extern f32 confettiDrag;
extern camera_t fastSpinPath2[];    // the move of view 15, one of the two of a fast spin
extern camera_t openingPath[];
extern camera_t fastSpinPath1[];    // the move of view 11, one of the two of a fast spin
extern camera_t unusedCameraPath[];   // a move no view plays
extern camera_t view14Path[];       // the move of view 14, which no code selects
extern camera_t nextRoundPath[];    // the move of view 13, between rounds
extern camera_t gameStartPath[];    // the move of view 12, at the start of a game
extern camera_t view16Path[];       // the move of view 16, which no code selects
extern s32 memEnd;
extern s32 D_8006DCDC;
extern s32 D_8006DCE0;
extern s32 D_8006DCE4;
extern s32 memStart;
extern s32 staticRom;
extern s32 staticSize;
extern s32 sceneDataRom;
extern s32 sceneDataSize;
extern s32 sceneDataRomEnd;         // sceneDataRom + sceneDataSize; nothing reads it
extern s32 bssEnd;                  // the end of the .bss; nothing reads it
extern s32 sfxCtlRom;
extern s32 sfxCtlRomEnd;
extern s32 sfxTblRom;
extern s32 D_8006DD10;
extern s32 D_8006DD14;
extern s32 D_8006DD18;
extern s32 D_8006DD1C;
extern s32 D_8006DD20;
extern s32 D_8006DD24;
extern s32 D_8006DD28;
extern s32 movieSizes[];
extern s32 celebrationMask[];  // zero, then a mask: StartCelebration decodes movie 22 through it
extern s32 vannaWalkMask[];  // a mask
extern s32 vannaAnim1Mask[];  // a mask
extern s32 vannaAnim5Mask[];  // a mask
extern s32 vannaAnim2Mask[];  // a mask
extern s32 vannaTurnMask[];  // a mask
extern s32 contestant0AnimMask[];  // a mask
extern s32 contestant0ClipMask1[];  // a mask
extern s32 contestant0StillMask[];  // a mask
extern s32 contestant1AnimMask[];  // a mask
extern s32 contestant1StillMask[];  // a mask
extern s32 contestant2AnimMask[];  // a mask
extern s32 contestant2StillMask[];  // a mask
extern s32 contestant2ClipMask0[];  // a mask
extern s32 contestant3AnimMask[];  // a mask
extern s32 contestant3StillMask[];  // a mask
extern s32 contestant3ClipMask0[];  // a mask
extern s32 contestant4AnimMask[];  // a mask
extern s32 contestant4StillMask[];  // a mask
extern s32 contestant4ClipMask0[];  // a mask
extern s32 contestant4ClipMask1[];  // a mask
extern s32 contestant5AnimMask[];  // a mask
extern s32 contestant5ClipMask0[];  // a mask
extern s32 contestant5StillMask[];  // a mask
extern long long int gfxUcodeData[];  // its data
extern s32 streamOpen;
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
extern OSScClient retraceClient;    // a scheduler client whose queue nothing reads
extern ALBankFile *sfxBankFile;
extern s32 openingFrame;
extern ALBankFile *seqBankFile;      // NOTE: nothing sets it
extern f32 cameraTurn[][2];         // [3], for each player what the buttons have added to roll and pitch of the camera
extern wedge_t wedges[];
extern s32 minRetraces;
extern u64 dram_stack[];            // the stack of the graphics microcode: SP_DRAM_STACK_SIZE8 bytes
extern s32 bonusTimeLeft;
extern s32 movieDone;
extern obj_t objst[];
extern s32 openingFrames;
extern s32 round;
extern s32 curGfxInfo;
extern s32 D_800B61A4;
extern s32 lightDir;
extern s8 bonusSlotLetters[];       // by bonusLetterSlots; 6 to 9 are bonusPicks
extern f32 hubAngle;                // the turn of the opening's hub, less a degree each retrace
extern s8 bonusPicks[];             // the bonus round's 3 consonants and vowel
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
extern s32 backdrop;
extern s32 *curMask;                // the clip mask the frames being decoded are stored through
extern Gfx *glistp;
extern s32 soundStates[];
extern s32 memStackTop;
extern s32 movieSound;
extern f32 cpuSkill;
extern proc_t procst[];
extern s32 prizeTaken;
extern s32 finalSpinValue;
extern s32 jackpot;
extern u8 category[];
extern u8 board[][21];
extern u8 solveBoard[][21];
extern u8 puzzleText[][21];
extern s8 puzzleTail[];             // a puzzle line's text after its 4th tab
extern u8 uncalled[];
extern OSMesgQueue gfxMsgQ;      // where the scheduler answers the graphics tasks and sends the retraces
extern s32 jackpotWon;
extern s32 movieToMemory;
extern s32 applause;
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
extern s32 vannaX;
extern s16 *moviePictures;
extern player_t players[];
extern OSMesgQueue retraceMsgQ;     // the queue of retraceClient
extern s32 shownJackpot;
extern s32 gameOver;
extern void *sceneData;
extern s32 canSpin;
extern s32 canBuyVowel;
extern s32 canSolve;
extern s32 newFrame;
extern tile_t topRow[];
extern tile_t secondRow[];
extern tile_t thirdRow[];
extern tile_t bottomRow[];
extern s32 curView;
extern s32 pauseStart;
extern AMDMABuffer dmaBuffs[];     // dmaBuffs[NUM_DMA_BUFFERS]
extern OSMesgQueue audDMAMessageQ;       // audDMAMessageQ
extern OSMesgQueue siLockQ;      // holds one message: LockSi takes it, UnlockSi puts it back
extern AMDMAState dmaState;        // dmaState
extern s32 bootArg;                 // the argument of the game's threads
extern camera_t *curCamera;
extern s32 blockOwners[];
extern u64 scheduleStack[];            // the stack of the scheduler: OS_SC_STACKSIZE bytes
extern u16 numSoundsPlaying;
extern s32 D_800BC6FC;
extern OSIoMesg audDMAIOMesgBuf[];       // audDMAIOMesgBuf[NUM_DMA_MESSAGES]
extern s32 finalSpin;
extern s32 memStackDepth;
extern void *staticSegment;           // segment 1: the display lists and pictures InitGraphics loads
extern s32 movieMemMark;
extern s32 numObjs;
extern s32 D_800BCA14;
extern s32 memStackEnd;
extern s32 pausedTime;
extern s32 movieSoundSlot;
extern s32 memStackBase;
extern s32 curMovie;
extern rumbleMsg_t rumbleMsg;
extern OSMesg gfxMsgBuf[];          // [8], the messages of gfxMsgQ
extern s32 contestantMemMark;
extern AMAudioMgr __am;        // __am
extern f32 wheelSpeed;
extern s32 solveCol;
extern ALSndPlayer sndPlayerData;      // the sound player sndPlayer points at
extern s32 D_800BCD50;
extern s32 gameMode;
extern OSScClient gfxClient;
extern u32 frameSize;              // frameSize
extern OSMesg contMsgBuf;
extern OSMesgQueue rumbleMsgQ;      // the queue of the rumble thread
extern u64 mainThreadStack[];            // the stack of the main thread: 0x2000 bytes
extern s32 inputCount;
extern ALCSPlayer *seqPlayers[];
extern s32 pausedMode;
extern u32 maxRSPCmds;              // maxRSPCmds
extern s32 curWedge;
extern s32 memStackMarks[];
extern s32 savedContestants[];
extern u32 pendingGfx;
extern s32 motorOn[];
extern s32 wedgeThird;
extern OSMesg retraceMsgBuf[];          // [8], the messages of retraceMsgQ
extern s32 bonusMusicSlot;
extern s32 logoSpread;              // how far the logo's pieces have flown out
extern s32 bonusConsonants;
extern f32 camX;
extern f32 camY;
extern f32 camZ;
extern f32 camRoll;
extern f32 camPitch;
extern f32 camHeading;
extern s32 lastInputTime;
extern s32 bonusVowels;
extern s32 numProcs;
extern s32 vowelsOnlyAnnounced;
extern u16 contPressed[];
extern rumble_t rumbles[];
extern OSMesgQueue *sched_cmdQ;      // the command queue of the scheduler
extern u16 *scoreDigits[][8];
extern gfxInfo_t gfxInfo[];
extern s32 curPlayer;
extern s32 contReading;
extern u64 retraceTime;
extern OSMesg audDMAMessageBuf[];          // audDMAMessageBuf[NUM_DMA_MESSAGES]
extern u16 zbuffer[];            // the depth buffer
extern u16 framebuffer0[];            // framebuffer0 and framebuffer1: the two framebuffers
extern u16 framebuffer1[];
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
void LoadSceneData( void );
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
void SeedRandom( s32 seed );
s32 Abs( s32 value );
void PrintNum( s32 num );
void FatalError( char *msg );
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
void *AllocMem( s32 size );
s32 PushMemStack( void );
void PopMemStack( s32 count );
void InitSiLock( void );
void LockSi( void );
void UnlockSi( void );
void StartGame( void );
struct procResult_s GameStartProc( proc_t *proc );
void BeginGame( void );
struct procResult_s OpeningProc( proc_t *proc );
struct procResult_s OpeningWheelProc( proc_t *proc );
struct procResult_s OpeningWedgeProc( proc_t *proc );
struct procResult_s TitleLetterProc( proc_t *proc );
struct procResult_s DebugCameraProc( proc_t *proc );
void DrawOpeningStudio( obj_t *obj, frame_t *frame );
void DrawOpeningHub( obj_t *obj, frame_t *frame );
void DrawOpeningPiece( obj_t *obj, frame_t *frame );
void DrawOpeningWheel( obj_t *obj, frame_t *frame );
void DrawSearchlights( obj_t *obj, frame_t *frame );
void DrawLogo( obj_t *obj, frame_t *frame );
struct procResult_s LogoProc( proc_t *proc );
void StartLogos( void );
void ShowNoController( void );
void RestartOpening( void );
void StartOpening( void );
struct procResult_s DemoProc( proc_t *proc );
void DemoStub( s32 arg0, s32 arg1 );
void StartDemo( void );
struct procResult_s WheelPullProc( proc_t *proc );
struct procResult_s PointerProc( proc_t *proc );
struct procResult_s DebugPointerProc( proc_t *proc );
struct procResult_s WheelStopProc( proc_t *proc );
struct procResult_s TurnWheel( proc_t *proc );
struct procResult_s WheelSpinProc( proc_t *proc );
struct procResult_s BoardLightsProc( proc_t *proc );
struct procResult_s WheelLightsProc( proc_t *proc );
struct procResult_s BaseLightsProc( proc_t *proc );
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
s32 GetSquareColor( tile_t *tile );
void DrawSquares( tile_t *tiles, s32 count, s32 blanks );
void DrawBoard( obj_t *obj, frame_t *frame );
void LightPlayer( s32 player );
void UnlightPlayers( void );
s32 GetLayerColor( layer_t *layer );
void SetScoreDigits( s32 total );
void DrawScores( obj_t *obj, frame_t *frame );
void DrawLetterBoard( obj_t *obj, frame_t *frame );
void DrawSetPiece( obj_t *obj, frame_t *frame );
void DrawWheelLights( obj_t *obj, frame_t *frame );
void DrawBackdrop( obj_t *obj, frame_t *frame );
void DrawWheel( obj_t *obj, frame_t *frame );
void DrawCeiling( obj_t *obj, frame_t *frame );
obj_t *MakeObj( proc_t *proc, Gfx *dl, objDraw_t draw, s32 cls );
void InitSquares( Gfx **dls, tile_t *tiles, s32 row, s32 count );
void InitBoard( void );
void ClearSquares( Gfx **dls, tile_t *tiles, s32 row, s32 count );
void StartBoardLights( void );
void StartWheelLights( void );
void ResetBoard( void );
void InitStage( void );
s32 IsBoardView( void );
s32 IsBoardHidden( void );
struct procResult_s CameraPathProc( proc_t *proc );
void SetView( obj_t *obj, s32 view );
void SetCameraView( s32 view );
struct procResult_s CameraProc( proc_t *proc );
void DrawCamera( obj_t *obj, frame_t *frame );
void InitCamera( proc_t *proc );
void CreateCamera( void );
s32 LoseTurn( void );
void NextTurn( void );
s32 MustLoseTurn( void );
void NextRound( void );
void FindWinner( void );
struct procResult_s AdjustCameraProc( proc_t *proc );
void SetGameView( s32 view, s32 cpu );
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
void DrawMovie64( obj_t *obj, frame_t *frame );
void DrawMovie96( obj_t *obj, frame_t *frame );
void StoreFrame96( u16 *pixels );
void DrawMovie112( obj_t *obj, frame_t *frame );
void DrawMovie( obj_t *obj, frame_t *frame );
void StoreFrame112( u16 *pixels );
void StoreFrame64x64( u16 *pixels );
void StoreFrame64x96( u16 *pixels );
void StoreFrame( void *pixels );
obj_t *MakeMovieObj( proc_t *proc, char *text, f32 x, f32 y, s32 movie );
void UpdateMovie( proc_t *proc );
void UpdateClip( proc_t *proc );
struct procResult_s MovieProc( proc_t *proc );
struct procResult_s ClipProc( proc_t *proc );
char *LoadMovie( s32 movie );
void PlayMovie( s32 movie, s32 event, s32 x, s32 y );
void PlayMovieCorner( s32 movie, s32 event );
void DecodeMovie( s32 movie, s32 count, s16 *pictures, s32 *mask );
void PlayClip( s32 movie, s32 *mask, obj_t *obj, s32 slot, s32 event );
void StopMovie( void );
void DrawMainMenu1( obj_t *obj, frame_t *frame );
void DrawContestantMenu( obj_t *obj, frame_t *frame );
void DrawMainMenu3( obj_t *obj, frame_t *frame );
void DrawSkillMenu( obj_t *obj, frame_t *frame );
void DrawRoundsMenu( obj_t *obj, frame_t *frame );
void SetImageFlash( image_t *images, s32 count, s32 flash );
void InitMainFlash( proc_t *proc, image_t *images, menuItem_t *item, s32 on );
void MenuUp( proc_t *proc, image_t *images, menuItem_t *items, s32 count );
void MenuDown( proc_t *proc, image_t *images, menuItem_t *items, s32 count );
void MenuLeft( proc_t *proc, image_t *images, menuItem_t *item, s32 skipAbsent );
void MenuRight( proc_t *proc, image_t *images, menuItem_t *item, s32 skipAbsent );
void SetControllers( void );
struct procResult_s MainMenu1Proc( proc_t *proc );
void SwitchImage( void );
struct procResult_s ContestantMenuProc( proc_t *proc );
struct procResult_s SkillMenuProc( proc_t *proc );
struct procResult_s RoundsMenuProc( proc_t *proc );
void SetContestantSounds( s32 player );
void ApplyOptions( void );
struct procResult_s MainMenu3Proc( proc_t *proc );
void InitMarquee( void );
void StartMainMenu1( void );
void StartContestantMenu( void );
void StartMainMenu3( void );
void StartSkillMenu( void );
void StartRoundsMenu( void );
void StartMenus( void );
void InitOptions( void );
obj_t *MakeScreenObj( proc_t *proc, Gfx *dl, objDraw_t draw, s32 cls );
u16 *GetImageTexture( image_t *image, s32 lit );
void DrawImageAt( image_t *image, s32 lit, s32 dx, s32 dy );
void DrawImage( image_t *image, s32 lit );
void DrawStatus( obj_t *obj, frame_t *frame );
void DrawBigNumber( obj_t *obj, frame_t *frame );
void DrawCreditsTitle( obj_t *obj, frame_t *frame );
void DrawLetterPick( obj_t *obj, frame_t *frame );
void DrawBonusPrize( obj_t *obj, frame_t *frame );
void DrawBonusTimer( obj_t *obj, frame_t *frame );
void DrawRetraces( s32 arg0, s32 arg1 );
void DrawPressStart( obj_t *obj, frame_t *frame );
void DrawBootScreen( obj_t *obj, frame_t *frame );
void DrawNoController( obj_t *obj, frame_t *frame );
void DrawPause( obj_t *obj, frame_t *frame );
void InitActionCursor( proc_t *proc );
void ClearCategory( void );
void DrawCategoryWheel( obj_t *obj, frame_t *frame );
struct procResult_s CategoryProc( proc_t *proc );
void InitCategory( void );
void SetScorePictures( s32 total );
void FlashScore( s32 player );
struct procResult_s JackpotRollProc( proc_t *proc );
void ShowJackpot( void );
void ShowTotal( void );
void MoveCursorLeft( proc_t *proc, s32 letters );
void MoveCursorRight( proc_t *proc, s32 letters, s32 sound );
void MoveCursorUp( proc_t *proc );
void MoveCursorDown( proc_t *proc );
void UnflashActions( void );
void ClearBonusLetters( void );
struct procResult_s ShowTotalProc( proc_t *proc );
struct procResult_s CreditsProc( proc_t *proc );
struct procResult_s ShowWinTotalProc( proc_t *proc );
struct procResult_s BonusLostProc( proc_t *proc );
struct procResult_s BonusTimerProc( proc_t *proc );
struct procResult_s ShowRetracesProc( proc_t *proc );
struct procResult_s BonusWonProc( proc_t *proc );
struct procResult_s BonusRoundProc( proc_t *proc );
void FlashPlayerStatus( void );
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
void StatusStub( void );
void StartBonusRound( void );
struct procResult_s FinalSpinProc( proc_t *proc );
struct procResult_s RoundTimerProc( proc_t *proc );
struct procResult_s DemoTimerProc( proc_t *proc );
struct procResult_s SolveTimerProc( proc_t *proc );
struct procResult_s FreeSpinTimerProc( proc_t *proc );
void StartFreeSpinTimer( void );
void StopFreeSpinTimer( void );
void StartSolveTimer( void );
void ResetSolveTimer( void );
void StartRoundTimer( void );
void StartDemoTimer( void );
void DrawContestant( obj_t *obj, frame_t *frame );
void DrawMenuContestant( obj_t *obj, frame_t *frame );
void DrawVanna( obj_t *obj, frame_t *frame );
void SetPicture( s16 *pixels, s32 slot );
void SetVannaPicture( s16 *pixels, s32 dir );
struct procResult_s AnimProc( proc_t *proc );
struct procResult_s VannaAnimProc( proc_t *proc );
void InitMenuAnim( s32 contestant, s32 slot, s32 x, s32 y, s32 z );
void InitAnim( s32 anim, s32 player );
void SetVannaStill( void );
proc_t *InitVannaAnim( s32 anim, s32 replace );
void SetVannaAnim( s32 anim );
void PlayContestantAnims( void );
void SetContestantsStill( void );
void InitContestants( void );
s32 PlayContestantClip( s32 clip, s32 event, s32 player );
void InitMenuContestants( void );
void HideOtherContestants( void );
void PauseGame( void );
struct procResult_s PauseProc( proc_t *proc );
void StartPauseProc( void );
struct procResult_s ApplauseProc( proc_t *proc );
void StartApplause( void );
void DrawConfetti( obj_t *obj, frame_t *frame );
struct procResult_s ConfettiProc( proc_t *proc );
void AddConfetti( s32 x, s32 xRange, s32 y, s32 yRange, s32 speedRange, s32 speedBase, s32 turnsRange,
                    s32 turnsBase );
struct procResult_s ConfettiBurstProc( proc_t *proc );

void StartCelebration( void );
void mpegStart( char *movie, s32 gamma );
s32 mpegNextFrame( void );
void fclose( void *stream );

#endif // WOF_H
