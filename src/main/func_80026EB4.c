#include "wof.h"


void func_80026EB4(void) {
    s32 i;

    do {
    } while (D_800BEDE4 != 0 && D_800B96AC < 100);
    func_80005700();
    D_800BCD54 = 7;
    for (i = 0; i < 3; i++) {
        D_800B9990[i].unk_018 = D_800BEDD8[i];
    }
    func_800174DC();
    func_80016B9C(19);
    func_80033334();
    D_800FB808 = 0;
    func_80026800();
}
