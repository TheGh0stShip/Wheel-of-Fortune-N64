#include "wof.h"

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
    t->list.t.ucode_boot = (u64 *)D_800349B8;
    t->list.t.ucode_boot_size = (int)D_80034A88 - (int)D_800349B8;
    t->list.t.flags = OS_TASK_DP_WAIT;
    t->list.t.ucode = (u64 *)D_80037298;
    t->list.t.ucode_data = (u64 *)D_80083BC8;
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
