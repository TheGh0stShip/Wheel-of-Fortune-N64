#include "wof.h"

void func_800289F4(obj_t *obj, frame_t *frame) {
    s32 i;

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, D_01021970);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    for (i = 0; i < 2; i++) {
        func_800278A8(&D_8005A760[i], 1);
    }
}
