#include "wof.h"

/*
=====================
func_80003CC8

guess: __amDMA of the audiomgr.c of the SDK demos, the DMA callback of the synthesizer. Returns
the address of sample data from the cartridge: from a buffer that already holds it, or else from
a free buffer that it starts a read into.
=====================
*/
s32 func_80003CC8( s32 addr, s32 len, void *state ) {
    void        *foundBuffer;
    s32         delta;
    s32         addrEnd;
    s32         buffEnd;
    AMDMABuffer *dmaPtr;
    AMDMABuffer *lastDmaPtr;

    lastDmaPtr = 0;
    dmaPtr = D_800BA5C8.firstUsed;
    addrEnd = addr + len;
    // the buffers are in address order
    while ( dmaPtr ) {
        buffEnd = dmaPtr->startAddr + DMA_BUFFER_LENGTH;
        if ( dmaPtr->startAddr > addr ) {
            break;
        } else if ( addrEnd <= buffEnd ) {
            dmaPtr->lastFrame = D_8004B7A8;
            foundBuffer = dmaPtr->ptr + addr - dmaPtr->startAddr;
            return (int)osVirtualToPhysical( foundBuffer );
        }
        lastDmaPtr = dmaPtr;
        dmaPtr = (AMDMABuffer *)dmaPtr->node.next;
    }
    // no buffer holds it: take one from the free list
    dmaPtr = D_800BA5C8.firstFree;
    D_800BA5C8.firstFree = (AMDMABuffer *)dmaPtr->node.next;
    alUnlink( (ALLink *)dmaPtr );
    if ( lastDmaPtr ) {
        alLink( (ALLink *)dmaPtr, (ALLink *)lastDmaPtr );
    } else if ( D_800BA5C8.firstUsed ) {
        lastDmaPtr = D_800BA5C8.firstUsed;
        D_800BA5C8.firstUsed = dmaPtr;
        dmaPtr->node.next = (ALLink *)lastDmaPtr;
        dmaPtr->node.prev = 0;
        lastDmaPtr->node.prev = (ALLink *)dmaPtr;
    } else {
        D_800BA5C8.firstUsed = dmaPtr;
        dmaPtr->node.next = 0;
        dmaPtr->node.prev = 0;
    }
    foundBuffer = dmaPtr->ptr;
    delta = addr & 0x1;
    addr -= delta;
    dmaPtr->startAddr = addr;
    dmaPtr->lastFrame = D_8004B7A8;
    osPiStartDma( &D_800BC700[D_8004B7AC++], OS_MESG_PRI_NORMAL, OS_READ, addr, foundBuffer,
                  DMA_BUFFER_LENGTH, &D_800BA598 );
    return (int)osVirtualToPhysical( foundBuffer ) + delta;
}
