#include "wof.h"

/*
=====================
func_80003944

guess: __amHandleFrameMsg of the audiomgr.c of the SDK demos. Queues the samples of the last
frame for output, has the synthesizer write the command list of this frame and sends it to the
scheduler as an audio task. Returns 0 if there was nothing to play. The count of the DMA buffers
in use, whose peak D_800B96B8 keeps, is not in the SDK source.
=====================
*/
u32 func_80003944( AudioInfo *info, AudioInfo *lastInfo ) {
    s16         *audioPtr;
    Acmd        *cmdp;
    s32         cmdLen;
    int         samplesLeft = 0;
    OSScTask    *t;
    s32         count;
    AMDMABuffer *dmaPtr;

    count = 0;
    dmaPtr = D_800BA5C8.firstUsed;
    while ( dmaPtr ) {
        count++;
        dmaPtr = (AMDMABuffer *)dmaPtr->node.next;
    }
    if ( count > D_800B96B8 ) {
        D_800B96B8 = count;
    }
    func_80003FDC();
    audioPtr = (s16 *)osVirtualToPhysical( info->data );
    if ( lastInfo ) {
        osAiSetNextBuffer( lastInfo->data, lastInfo->frameSamples << 2 );
    }
    // how many samples this frame needs to keep the DAC full
    samplesLeft = osAiGetLength() >> 2;
    info->frameSamples = ( 16 + ( D_800BCD64 - samplesLeft + EXTRA_SAMPLES ) ) & ~0xf;
    if ( info->frameSamples < D_800B96BC ) {
        info->frameSamples = D_800B96BC;
    }
    cmdp = alAudioFrame( D_800BCA68.ACMDList[D_8004B7B0], &cmdLen, audioPtr, info->frameSamples );
    if ( cmdLen == 0 ) {
        return 0;
    }
    t = &info->task;
    t->next = 0;
    t->msgQ = &D_800BCA68.audioReplyMsgQ;
    t->msg = (OSMesg)&info->msg;
    t->flags = OS_SC_NEEDS_RSP;
    t->list.t.data_ptr = (u64 *)D_800BCA68.ACMDList[D_8004B7B0];
    t->list.t.data_size = ( cmdp - D_800BCA68.ACMDList[D_8004B7B0] ) * sizeof( Acmd );
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
    osSendMesg( D_800BEEA0, (OSMesg)t, OS_MESG_BLOCK );
    D_8004B7B0 ^= 1;
    return 1;
}
