#include "wof.h"

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
