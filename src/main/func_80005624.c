#include "wof.h"

void func_80005624(void) {
    s32 size;

    size = D_8006DCF0;
    D_800BEE2C = D_800BEE30 = D_800BEE34 = D_800BEE3C = D_800BEE40 = D_800BEE44 = 0.0f;
    D_800BCA08 = func_8000B924(size);
    func_80006828(D_8006DCEC, D_800BCA08, size);
    D_800DD360 = 2;
    D_800DD380 = &D_803B5000;
    D_800FB7E0 = 2;
    D_800FB800 = &D_803DA800;
    func_8004B198(64);
}
