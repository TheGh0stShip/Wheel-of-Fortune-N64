#include "wof.h"

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
