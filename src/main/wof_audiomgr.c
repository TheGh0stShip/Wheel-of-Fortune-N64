// wof_audiomgr.c -- the audio manager: its thread, its tasks and the DMA of samples
//
// guess: the audiomgr.c of the SDK's demos, from the lineage, with its functions in that file's
// order. One object from amCreateAudioMgr, whose RCS run opens it, to __clearAudioDMA: __amMain,
// __amDMA and __amDmaNew end off an 8-byte boundary with the next function right after; the data
// ties the rest: nextDMA and firstTime lie 4 bytes past an 8-byte boundary, where no object starts,
// so audFrameCt and nextDMA (__amMain, __amDMA, __clearAudioDMA) are one object's, and so are
// curAcmdList (__amHandleFrameMsg) and __amHandleDoneMsg's static firstTime; audiomgr.c defines
// all three globals together. Where the object ends after __clearAudioDMA the text does not say.

#include "wof.h"

// The #ident line of the system header this object included: the original assembler put the string
// into the read-only data, which it opens. The header is not in this tree, so its line stands here.
#ident "$Revision: 1.17 $"

u32 audFrameCt = 0;
u32 nextDMA = 0;
u32 curAcmdList = 0;

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

/*
=====================
__amMain

guess: __amMain of the audiomgr.c of the SDK demos, the audio thread. Builds an audio task on
every retrace message and waits for the scheduler to report it done.
=====================
*/
void __amMain( void *arg ) {
    u32         validTask;
    u32         done;
    AudioMsg    *msg;
    AudioInfo   *lastInfo;
    OSScClient  client;

    done = 0;
    lastInfo = 0;
    osScAddClient( &sc, &client, &__am.audioFrameMsgQ );
    while ( !done ) {
        osRecvMesg( &__am.audioFrameMsgQ, (OSMesg *)&msg, OS_MESG_BLOCK );
        switch ( msg->gen.type ) {
        case OS_SC_RETRACE_MSG:
            validTask = __amHandleFrameMsg( __am.audioInfo[audFrameCt % 3], lastInfo );
            if ( validTask ) {
                // wait for the done message
                osRecvMesg( &__am.audioReplyMsgQ, (OSMesg *)&msg, OS_MESG_BLOCK );
                __amHandleDoneMsg( msg->done.info );
                lastInfo = msg->done.info;
            }
            break;
        case OS_SC_PRE_NMI_MSG:
            break;
        case QUIT_MSG:
            done = 1;
            break;
        default:
            break;
        }
    }
    alClose( &__am.g );
}

/*
=====================
__amHandleFrameMsg

guess: __amHandleFrameMsg of the audiomgr.c of the SDK demos. Queues the samples of the last
frame for output, has the synthesizer write the command list of this frame and sends it to the
scheduler as an audio task. Returns 0 if there was nothing to play. The count of the DMA buffers
in use, whose peak maxDmaBuffsUsed keeps, is not in the SDK source.
=====================
*/
u32 __amHandleFrameMsg( AudioInfo *info, AudioInfo *lastInfo ) {
    s16         *audioPtr;
    Acmd        *cmdp;
    s32         cmdLen;
    int         samplesLeft = 0;
    OSScTask    *t;
    s32         count;
    AMDMABuffer *dmaPtr;

    count = 0;
    dmaPtr = dmaState.firstUsed;
    while ( dmaPtr ) {
        count++;
        dmaPtr = (AMDMABuffer *)dmaPtr->node.next;
    }
    if ( count > maxDmaBuffsUsed ) {
        maxDmaBuffsUsed = count;
    }
    __clearAudioDMA();
    audioPtr = (s16 *)osVirtualToPhysical( info->data );
    if ( lastInfo ) {
        osAiSetNextBuffer( lastInfo->data, lastInfo->frameSamples << 2 );
    }
    // how many samples this frame needs to keep the DAC full
    samplesLeft = osAiGetLength() >> 2;
    info->frameSamples = ( 16 + ( frameSize - samplesLeft + EXTRA_SAMPLES ) ) & ~0xf;
    if ( info->frameSamples < minFrameSize ) {
        info->frameSamples = minFrameSize;
    }
    cmdp = alAudioFrame( __am.ACMDList[curAcmdList], &cmdLen, audioPtr, info->frameSamples );
    if ( cmdLen == 0 ) {
        return 0;
    }
    t = &info->task;
    t->next = 0;
    t->msgQ = &__am.audioReplyMsgQ;
    t->msg = (OSMesg)&info->msg;
    t->flags = OS_SC_NEEDS_RSP;
    t->list.t.data_ptr = (u64 *)__am.ACMDList[curAcmdList];
    t->list.t.data_size = ( cmdp - __am.ACMDList[curAcmdList] ) * sizeof( Acmd );
    t->list.t.type = M_AUDTASK;
    t->list.t.ucode_boot = (u64 *)rspbootTextStart;
    t->list.t.ucode_boot_size = (int)rspbootTextEnd - (int)rspbootTextStart;
    t->list.t.flags = OS_TASK_DP_WAIT;
    t->list.t.ucode = (u64 *)aspMainTextStart;
    t->list.t.ucode_data = (u64 *)aspMainDataStart;
    t->list.t.ucode_data_size = SP_UCODE_DATA_SIZE;
    t->list.t.dram_stack = (u64 *)NULL;
    t->list.t.dram_stack_size = 0;
    t->list.t.output_buff = (u64 *)NULL;
    t->list.t.output_buff_size = 0;
    t->list.t.yield_data_ptr = NULL;
    t->list.t.yield_data_size = 0;
    osSendMesg( sched_cmdQ, (OSMesg)t, OS_MESG_BLOCK );
    curAcmdList ^= 1;
    return 1;
}

/*
=====================
__amHandleDoneMsg

guess: __amHandleDoneMsg of the audiomgr.c of the SDK demos. Notes when the audio interface ran out
of samples; the note is compiled out.
=====================
*/
void __amHandleDoneMsg(AudioInfo *info) {
    u32 samplesLeft;
    static s32 firstTime = 1;

    samplesLeft = osAiGetLength() >> 2;
    if (samplesLeft == 0 && firstTime == 0) {
        firstTime = 0;
    }
}

/*
=====================
__amDMA

guess: __amDMA of the audiomgr.c of the SDK demos, the DMA callback of the synthesizer. Returns
the address of sample data from the cartridge: from a buffer that already holds it, or else from
a free buffer that it starts a read into.
=====================
*/
s32 __amDMA( s32 addr, s32 len, void *state ) {
    void        *foundBuffer;
    s32         delta;
    s32         addrEnd;
    s32         buffEnd;
    AMDMABuffer *dmaPtr;
    AMDMABuffer *lastDmaPtr;

    lastDmaPtr = 0;
    dmaPtr = dmaState.firstUsed;
    addrEnd = addr + len;
    // the buffers are in address order
    while ( dmaPtr ) {
        buffEnd = dmaPtr->startAddr + DMA_BUFFER_LENGTH;
        if ( dmaPtr->startAddr > addr ) {
            break;
        } else if ( addrEnd <= buffEnd ) {
            dmaPtr->lastFrame = audFrameCt;
            foundBuffer = dmaPtr->ptr + addr - dmaPtr->startAddr;
            return (int)osVirtualToPhysical( foundBuffer );
        }
        lastDmaPtr = dmaPtr;
        dmaPtr = (AMDMABuffer *)dmaPtr->node.next;
    }
    // no buffer holds it: take one from the free list
    dmaPtr = dmaState.firstFree;
    dmaState.firstFree = (AMDMABuffer *)dmaPtr->node.next;
    alUnlink( (ALLink *)dmaPtr );
    if ( lastDmaPtr ) {
        alLink( (ALLink *)dmaPtr, (ALLink *)lastDmaPtr );
    } else if ( dmaState.firstUsed ) {
        lastDmaPtr = dmaState.firstUsed;
        dmaState.firstUsed = dmaPtr;
        dmaPtr->node.next = (ALLink *)lastDmaPtr;
        dmaPtr->node.prev = 0;
        lastDmaPtr->node.prev = (ALLink *)dmaPtr;
    } else {
        dmaState.firstUsed = dmaPtr;
        dmaPtr->node.next = 0;
        dmaPtr->node.prev = 0;
    }
    foundBuffer = dmaPtr->ptr;
    delta = addr & 0x1;
    addr -= delta;
    dmaPtr->startAddr = addr;
    dmaPtr->lastFrame = audFrameCt;
    osPiStartDma( &audDMAIOMesgBuf[nextDMA++], OS_MESG_PRI_NORMAL, OS_READ, addr, foundBuffer,
                  DMA_BUFFER_LENGTH, &audDMAMessageQ );
    return (int)osVirtualToPhysical( foundBuffer ) + delta;
}

/*
=====================
__amDmaNew

guess: __amDmaNew of the audiomgr.c of the SDK demos. The synthesizer calls it once for each
voice to get the DMA callback.
=====================
*/
ALDMAproc __amDmaNew( AMDMAState **state ) {
    int i;  /* NOTE: unused in the original, as in the SDK source */

    if ( !dmaState.initialized ) {
        dmaState.firstUsed = 0;
        dmaState.firstFree = &dmaBuffs[0];
        dmaState.initialized = 1;
    }
    *state = &dmaState;
    return __amDMA;
}

/*
=====================
__clearAudioDMA

guess: __clearAudioDMA of the audiomgr.c of the SDK demos. Once a frame: takes the finished
reads off the message queue and puts the buffers that went unused for more than FRAME_LAG frames
back on the free list.
=====================
*/
void __clearAudioDMA( void ) {
    u32         i;
    OSIoMesg    *iomsg;
    AMDMABuffer *dmaPtr;
    AMDMABuffer *nextPtr;

    // no blocking: a read that is not done is an audio overrun
    for ( i = 0; i < nextDMA; i++ ) {
        if ( osRecvMesg( &audDMAMessageQ, (OSMesg *)&iomsg, OS_MESG_NOBLOCK ) == -1 ) {
            PRINTF( "Dma not done\n" );
        }
    }
    dmaPtr = dmaState.firstUsed;
    while ( dmaPtr ) {
        nextPtr = (AMDMABuffer *)dmaPtr->node.next;
        if ( dmaPtr->lastFrame + FRAME_LAG < audFrameCt ) {
            if ( dmaState.firstUsed == dmaPtr ) {
                dmaState.firstUsed = (AMDMABuffer *)dmaPtr->node.next;
            }
            alUnlink( (ALLink *)dmaPtr );
            if ( dmaState.firstFree ) {
                alLink( (ALLink *)dmaPtr, (ALLink *)dmaState.firstFree );
            } else {
                dmaState.firstFree = dmaPtr;
                dmaPtr->node.next = 0;
                dmaPtr->node.prev = 0;
            }
        }
        dmaPtr = nextPtr;
    }
    nextDMA = 0;
    audFrameCt++;
}
