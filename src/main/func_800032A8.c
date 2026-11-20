#include "wof.h"

/*
=====================
func_800032A8

guess: amCreateAudioMgr of the audiomgr.c of the SDK demos. Starts the synthesizer, allocates
the DMA buffers, the command lists and the output buffers, and starts the audio thread.
=====================
*/
void func_800032A8( ALSynConfig *c, OSPri pri, amConfig *amc ) {
    u32 i;
    f32 fsize;

    D_800BA5C8.initialized = FALSE;
    D_800B96B8 = 0;
    c->dmaproc = func_80003F64;
    c->outputRate = osAiSetFrequency( amc->outputRate );
    // the samples of a frame, from the video field rate and the output rate
    fsize = (f32)amc->framesPerField * c->outputRate / (f32)60;
    D_800BCD64 = (s32)fsize;
    if ( D_800BCD64 < fsize ) {
        D_800BCD64++;
    }
    if ( D_800BCD64 & 0xf ) {
        D_800BCD64 = ( D_800BCD64 & ~0xf ) + 0x10;
    }
    D_800B96BC = D_800BCD64 - 16;
    D_800B9950 = D_800BCD64 + EXTRA_SAMPLES + 16;
    alInit( &D_800BCA68.g, c );
    D_800BA2C8[0].node.prev = 0;
    D_800BA2C8[0].node.next = 0;
    for ( i = 0; i < NUM_DMA_BUFFERS - 1; i++ ) {
        alLink( (ALLink *)&D_800BA2C8[i + 1], (ALLink *)&D_800BA2C8[i] );
        D_800BA2C8[i].ptr = alHeapAlloc( c->heap, 1, DMA_BUFFER_LENGTH );
    }
    // the last buffer is linked already, but still needs its memory
    D_800BA2C8[i].ptr = alHeapAlloc( c->heap, 1, DMA_BUFFER_LENGTH );
    for ( i = 0; i < NUM_ACMD_LISTS; i++ ) {
        D_800BCA68.ACMDList[i] = (Acmd *)alHeapAlloc( c->heap, 1, amc->maxACMDSize * sizeof( Acmd ) );
    }
    D_800BEDA4 = amc->maxACMDSize;
    for ( i = 0; i < NUM_OUTPUT_BUFFERS; i++ ) {
        D_800BCA68.audioInfo[i] = (AudioInfo *)alHeapAlloc( c->heap, 1, sizeof( AudioInfo ) );
        D_800BCA68.audioInfo[i]->msg.done.type = OS_SC_DONE_MSG;
        D_800BCA68.audioInfo[i]->msg.done.info = D_800BCA68.audioInfo[i];
        D_800BCA68.audioInfo[i]->data = alHeapAlloc( c->heap, 1, 4 * D_800B9950 );
    }
    osCreateMesgQueue( &D_800BCA68.audioReplyMsgQ, D_800BCA68.audioReplyMsgBuf, MAX_MESGS );
    osCreateMesgQueue( &D_800BCA68.audioFrameMsgQ, D_800BCA68.audioFrameMsgBuf, MAX_MESGS );
    osCreateMesgQueue( &D_800BA598, D_800FB818, NUM_DMA_MESSAGES );
    osCreateThread( &D_800BCA68.thread, 3, func_800037A0, 0,
                    (void *)( D_800A50A0 + AUDIO_STACKSIZE / sizeof( u64 ) ), pri );
    osStartThread( &D_800BCA68.thread );
}
