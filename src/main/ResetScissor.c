#include "wof.h"

/*
=====================
ResetScissor

Sets the scissor back to the whole screen between the two DrawObjs passes.
=====================
*/
void ResetScissor(frame_t *frame) {
    s32 unused;  /* NOTE: unused in the original */

    gDPPipeSync(glistp++);
    gDPSetScissor(glistp++, G_SC_NON_INTERLACE, 0, 0, 320, 240);
    gDPPipeSync(glistp++);
    gDPPipeSync(glistp++);
}
