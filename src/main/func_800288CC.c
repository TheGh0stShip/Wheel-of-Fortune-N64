#include "wof.h"

void func_800288CC(obj_t *obj, frame_t *frame) {
    s32 i;

    gDPPipeSync(D_800B81E8++);
    gSPDisplayList(D_800B81E8++, D_01021970);
    gDPSetCycleType(D_800B81E8++, G_CYC_COPY);
    for (i = 0; i < 8; i++) {
        func_800278A8(&D_8005A620[i], 1);
    }
}
