#include "wof.h"

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
