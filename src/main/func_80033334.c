#include "wof.h"

void func_80033334(void) {
    s32 pad0[2];
    s32 i;
    s32 size;
    s32 sp20;

    sp20 = 0x2000000;
    D_800BCA60 = func_8000B978();
    for (i = 0; i < 6; i++) {
        size = D_8005C718[i].width * D_8005C718[i].height * 2;
        D_8005C718[i].unk_18 = func_8000B924(size * D_8005C718[i].count);
        func_80021B4C(D_8005C718[i].movie, D_8005C718[i].count, D_8005C718[i].unk_18, D_8005C718[i].unk_20);
    }
    D_800B96AC = 0;
}
