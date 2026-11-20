#include "wof.h"

void func_80005624(void) {
    s32 size;

    size = D_8006DCF0;
    D_800BEE2C = D_800BEE30 = D_800BEE34 = D_800BEE3C = D_800BEE40 = D_800BEE44 = 0.0f;
    D_800BCA08 = func_8000B924(size);
    func_80006828(D_8006DCEC, D_800BCA08, size);
    D_800BEF08[0].msg.type = OS_SC_DONE_MSG;
    D_800BEF08[0].framebuffer = D_803B5000;
    D_800BEF08[1].msg.type = OS_SC_DONE_MSG;
    D_800BEF08[1].framebuffer = D_803DA800;
    osViSetSpecialFeatures(64);
}
