// library.h -- what the game uses of the SDK libraries, until the SDK headers are in the tree

// The library units are not reconstructed yet, so the game calls most of them by address. Each
// prototype below is the SDK signature of the function the donor source places at that address, and
// the game's call sites agree with it. The SDK name in the comment is not verified. `void *` stands
// for a pointer to an SDK structure (OSMesgQueue, OSThread, ALSndPlayer and so on).
// This file gives way to the SDK's own headers.

#ifndef LIBRARY_H
#define LIBRARY_H

#include "types.h"

// <PR/gbi.h>: a 4x4 fixed-point matrix as the RSP reads it
typedef long Mtx_t[4][4];

typedef union {
    Mtx_t           m;
    long long int   force_structure_alignment;
} Mtx;

// <PR/gbi.h>: one display list command. The SDK's Gfx is a union of command layouts whose plain
// form is `words.w0`, `words.w1`; the game sources write the two words directly.
typedef struct {
    u32 w0;
    u32 w1;
} Gfx;

//
// functions, in address order
//
u32     func_80038748( void );                                      // osAiGetLength
s32     func_80038758( u32 frequency );                             // osAiSetFrequency
s32     func_800388B8( void *bufPtr, u32 size );                    // osAiSetNextBuffer
void    osCreatePiManager();                                        // 0x80038998
void    func_800396B8( void *sndp, f32 pitch );                     // alSndpSetPitch
void    func_80039718( void *sndp, s16 vol );                       // alSndpSetVol
void    func_80039778( void *sndp, u8 pan );                        // alSndpSetPan
void    func_800397D8( void *sndp, u8 mix );                        // alSndpSetFXMix
void    *func_80039980( void *cmdList, s32 *cmdLen, s16 *outBuf, s32 outLen );  // alAudioFrame
s32     func_80039F18( void *pfs );                                 // osMotorStop
s32     func_8003A080( void *pfs );                                 // osMotorStart
s32     func_8003A368( void *mq, void *pfs, int channel );          // osMotorInit
void    func_8003A538( void *ln );                                  // alUnlink
void    func_8003A568( void *ln, void *to );                        // alLink
void    func_8003A58C( void *glob );                                // alClose
void    func_8003A5C4( void *g, void *c );                          // alInit
void    func_8003A5F8( void *heap, u8 *base, s32 length );          // alHeapInit
// alHeapDBAlloc
void    *func_8003A638( const char *file, s32 line, void *heap, s32 count, s32 size );
void    func_8003B378( void *seqp );                                // alCSPPlay
void    func_8003B3A8( void *seqp, void *b );                       // alCSPSetBank
void    func_8003B944( void *seq, u8 *ptr );                        // alCSeqNew
void    func_8003BEA8( f32 mf[4][4], f32 r, f32 p, f32 h );         // guRotateRPYF
void    func_8003BFF4( Mtx *m, f32 r, f32 p, f32 h );               // guRotateRPY
void    func_8003C048( f32 mf[4][4], f32 x, f32 y, f32 z );         // guScaleF
void    func_8003C09C( Mtx *m, f32 x, f32 y, f32 z );               // guScale
void    func_8003C2A8( f32 mf[4][4], f32 x, f32 y, f32 z );         // guTranslateF
void    func_8003C2F0( Mtx *m, f32 x, f32 y, f32 z );               // guTranslate
void    osSetThreadPri();                                           // 0x8003CB38
s32     func_8003CC18( s32 arg0, s32 arg1 );                        // not identified
s32     func_8003CCC8( s32 arg0, s32 arg1 );                        // not identified
void    func_8003CDE8( void *sndp );                                // alSndpStop
s32     func_8003CE38( void *sndp );                                // alSndpGetState
int     func_8003CE58( void );                                      // guRandom
int     guRandom( void );                                           // 0x8003CE58, the same function
// guPerspective
void    func_8003E248( Mtx *m, u16 *perspNorm, f32 fovy, f32 aspect, f32 near, f32 far, f32 scale );
u32     func_8003E2A8( void );                                      // osPiGetStatus
s32     func_8003E318( void *mq, void *msg, s32 flag );             // osRecvMesg
s32     osRecvMesg();                                               // 0x8003E318, the same function
s32     func_8003E4B8( void *mq, void *msg, s32 flag );             // osSendMesg
s32     osSendMesg();                                               // 0x8003E4B8, the same function
void    func_8003E608( s32 event, void *mq, void *msg );            // osSetEventMesg
// osCreateThread
void    func_8003E6C8( void *thread, s32 id, void ( *entry )( void * ), void *arg, void *stack,
                       s32 priority );
void    osCreateThread();                                           // 0x8003E6C8, the same function
void    func_8003EA1C( void *file, u8 *table );                     // alBnkfNew
u32     func_8003FF78( void *addr );                                // osVirtualToPhysical
void    func_80041018( f32 mf[4][4], f32 nf[4][4], f32 res[4][4] ); // guMtxCatF
void    func_80041188( void *seqp, void *seq );                     // alCSPSetSeq
void    func_800411C8( void *seqp );                                // alCSPStop
void    func_800422B8( void *seqp, void *c );                       // alCSPNew
void    func_800447D8( void *thread );                              // osStartThread
void    osStartThread();                                            // 0x800447D8, the same function
u64     func_80044988( void );                                      // osGetTime
void    func_80044E38( void );                                      // osInitialize
s32     func_800453B8( s32 arg0, s32 arg1 );                        // not identified
void    func_80045498( void *mq, void *msg, s32 count );            // osCreateMesgQueue
void    osCreateMesgQueue();                                        // 0x80045498, the same function
// osPiStartDma
s32     func_80045628( void *mb, s32 priority, s32 direction, u32 devAddr, void *dramAddr, u32 size,
                       void *mq );
s32     func_80046808( void *mq, void *pfs, int channel );          // osPfsInit
s32     func_800481F8( void *mq );                                  // osContStartReadData
void    func_800482BC( void *data );                                // osContGetReadData
s32     func_80048458( void *mq, u8 *bitpattern, void *data );      // osContInit
void    *func_800491A8( void *sc );                                 // osScGetCmdQ
void    func_80049238( void *sc, void *c, void *msgQ );             // osScAddClient
// osCreateScheduler
void    func_80049288( void *sc, void *stack, s32 priority, u8 mode, u8 numFields );
s16     func_80049EB8( void *sndp, void *sound );                   // alSndpAllocate
void    func_80049F58( void *sndp, s16 id );                        // alSndpDeallocate
void    func_80049FA8( void *sndp, s16 id );                        // alSndpSetSound
void    func_80049FC8( void *sndp );                                // alSndpPlay
// guLookAt
void    func_8004A460( Mtx *m, f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp,
                       f32 yUp, f32 zUp );
void    func_8004AABC( void *sndp, void *c );                       // alSndpNew
void    func_8004B198( u32 func );                                  // osViSetSpecialFeatures

#endif // LIBRARY_H
