#include "wof.h"

/*
=====================
func_80003F64

guess: __amDmaNew of the audiomgr.c of the SDK demos. The synthesizer calls it once for each
voice to get the DMA callback.
=====================
*/
ALDMAproc func_80003F64( AMDMAState **state ) {
    int i;  /* NOTE: unused in the original, as in the SDK source */

    if ( !D_800BA5C8.initialized ) {
        D_800BA5C8.firstUsed = 0;
        D_800BA5C8.firstFree = &D_800BA2C8[0];
        D_800BA5C8.initialized = 1;
    }
    *state = &D_800BA5C8;
    return func_80003CC8;
}
