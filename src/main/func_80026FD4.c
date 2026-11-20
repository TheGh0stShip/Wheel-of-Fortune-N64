#include "wof.h"

void func_80026FD4(void) {
    s32 i;
    s32 count;

    D_800B8298 = 0.65f;
    D_800B96C0 = 6;
    for (i = 0; i < 3; i++) {
        D_800584C8[i].sel = 4;
        D_800B9990[i].unk_014 = 4;
        D_800B9990[i].unk_018 = i;
        D_800BEDD8[i] = i;
        func_80009900(D_800B9990[i].unk_01C, D_8005A498[i]);
    }
    count = 0;
    i = 0;
    while (i < 4) {
        if ((D_800B96C4 >> i) % 2 != 0) {
            D_800584C8[count].sel = i;
            D_800B9990[count].unk_014 = i;
            count++;
        }
        if (count >= 3) {
            break;
        }
        i++;
    }
    D_80058E70[0].sel = 1;
    D_80058FC8[0].sel = 3;
}
