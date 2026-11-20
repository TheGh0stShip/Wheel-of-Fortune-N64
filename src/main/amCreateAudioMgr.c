#include "wof.h"

/*
=====================
amCreateAudioMgr

guess: amCreateAudioMgr of the audiomgr.c of the SDK demos. Starts the synthesizer, allocates
the DMA buffers, the command lists and the output buffers, and starts the audio thread.
=====================
*/
void amCreateAudioMgr( ALSynConfig *c, OSPri pri, amConfig *amc ) {
    u32 i;
    f32 fsize;

    dmaState.initialized = FALSE;
    maxDmaBuffsUsed = 0;
    c->dmaproc = __amDmaNew;
    c->outputRate = osAiSetFrequency( amc->outputRate );
    // the samples of a frame, from the video field rate and the output rate
    fsize = (f32)amc->framesPerField * c->outputRate / (f32)60;
    frameSize = (s32)fsize;
    if ( frameSize < fsize ) {
        frameSize++;
    }
    if ( frameSize & 0xf ) {
        frameSize = ( frameSize & ~0xf ) + 0x10;
    }
    minFrameSize = frameSize - 16;
    maxFrameSize = frameSize + EXTRA_SAMPLES + 16;
    alInit( &__am.g, c );
    dmaBuffs[0].node.prev = 0;
    dmaBuffs[0].node.next = 0;
    for ( i = 0; i < NUM_DMA_BUFFERS - 1; i++ ) {
        alLink( (ALLink *)&dmaBuffs[i + 1], (ALLink *)&dmaBuffs[i] );
        dmaBuffs[i].ptr = alHeapAlloc( c->heap, 1, DMA_BUFFER_LENGTH );
    }
    // the last buffer is linked already, but still needs its memory
    dmaBuffs[i].ptr = alHeapAlloc( c->heap, 1, DMA_BUFFER_LENGTH );
    for ( i = 0; i < NUM_ACMD_LISTS; i++ ) {
        __am.ACMDList[i] = (Acmd *)alHeapAlloc( c->heap, 1, amc->maxACMDSize * sizeof( Acmd ) );
    }
    maxRSPCmds = amc->maxACMDSize;
    for ( i = 0; i < NUM_OUTPUT_BUFFERS; i++ ) {
        __am.audioInfo[i] = (AudioInfo *)alHeapAlloc( c->heap, 1, sizeof( AudioInfo ) );
        __am.audioInfo[i]->msg.done.type = OS_SC_DONE_MSG;
        __am.audioInfo[i]->msg.done.info = __am.audioInfo[i];
        __am.audioInfo[i]->data = alHeapAlloc( c->heap, 1, 4 * maxFrameSize );
    }
    osCreateMesgQueue( &__am.audioReplyMsgQ, __am.audioReplyMsgBuf, MAX_MESGS );
    osCreateMesgQueue( &__am.audioFrameMsgQ, __am.audioFrameMsgBuf, MAX_MESGS );
    osCreateMesgQueue( &audDMAMessageQ, audDMAMessageBuf, NUM_DMA_MESSAGES );
    osCreateThread( &__am.thread, 3, __amMain, 0,
                    (void *)( audioStack + AUDIO_STACKSIZE / sizeof( u64 ) ), pri );
    osStartThread( &__am.thread );
}
