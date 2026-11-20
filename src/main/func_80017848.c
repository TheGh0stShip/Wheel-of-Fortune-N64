#include "wof.h"


void func_80017848(void) {
    s32 i;
    s32 max;

    max = 0;
    D_800FB808 = 0;
    for (i = 0; i < 3; i++) {
        if (D_800B9990[i].unk_004 > max) {
            max = D_800B9990[i].unk_004;
            D_800FB808 = i;
        }
    }
    func_800133C8();
    func_80029BFC(D_800FB808);
}
