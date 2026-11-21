#include "wof.h"

void func_800288CC(obj_t *obj, frame_t *frame) {
    s32 i;

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, D_01021970);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    for (i = 0; i < 8; i++) {
        DrawImage(&D_8005A620[i], 1);
    }
}
