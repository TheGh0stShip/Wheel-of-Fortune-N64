#include "wof.h"

void ResetScissor(frame_t *frame) {
    s32 unused;  /* NOTE: unused in the original */

    gDPPipeSync(glistp++);
    gDPSetScissor(glistp++, G_SC_NON_INTERLACE, 0, 0, 320, 240);
    gDPPipeSync(glistp++);
    gDPPipeSync(glistp++);
}
