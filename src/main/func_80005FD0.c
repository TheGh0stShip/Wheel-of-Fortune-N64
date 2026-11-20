#include "wof.h"

void func_80005FD0(s32 arg0) {
    s32 unused;  /* NOTE: unused in the original */

    gDPPipeSync(D_800B81E8++);
    gDPSetScissor(D_800B81E8++, G_SC_NON_INTERLACE, 0, 0, 320, 240);
    gDPPipeSync(D_800B81E8++);
    gDPPipeSync(D_800B81E8++);
}
