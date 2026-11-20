#include "wof.h"

/*
=====================
func_80003FDC

guess: __clearAudioDMA of the audiomgr.c of the SDK demos. Once a frame: takes the finished
reads off the message queue and puts the buffers that went unused for more than FRAME_LAG frames
back on the free list.
=====================
*/
void func_80003FDC( void ) {
    u32         i;
    OSIoMesg    *iomsg;
    AMDMABuffer *dmaPtr;
    AMDMABuffer *nextPtr;

    // no blocking: a read that is not done is an audio overrun
    for ( i = 0; i < D_8004B7AC; i++ ) {
        if ( osRecvMesg( &D_800BA598, (OSMesg *)&iomsg, OS_MESG_NOBLOCK ) == -1 ) {
            PRINTF( "Dma not done\n" );
        }
    }
    dmaPtr = D_800BA5C8.firstUsed;
    while ( dmaPtr ) {
        nextPtr = (AMDMABuffer *)dmaPtr->node.next;
        if ( dmaPtr->lastFrame + FRAME_LAG < D_8004B7A8 ) {
            if ( D_800BA5C8.firstUsed == dmaPtr ) {
                D_800BA5C8.firstUsed = (AMDMABuffer *)dmaPtr->node.next;
            }
            alUnlink( (ALLink *)dmaPtr );
            if ( D_800BA5C8.firstFree ) {
                alLink( (ALLink *)dmaPtr, (ALLink *)D_800BA5C8.firstFree );
            } else {
                D_800BA5C8.firstFree = dmaPtr;
                dmaPtr->node.next = 0;
                dmaPtr->node.prev = 0;
            }
        }
        dmaPtr = nextPtr;
    }
    D_8004B7AC = 0;
    D_8004B7A8++;
}
