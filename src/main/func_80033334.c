#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u8 unk_0C[0xC];
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
} Entry;

extern Entry D_8005C718[];

void func_80033334(void) {
    s32 pad0[2];
    s32 i;
    s32 size;
    s32 sp20;

    sp20 = 0x2000000;
    D_800BCA60 = func_8000B978();
    for (i = 0; i < 6; i++) {
        size = D_8005C718[i].unk_00 * D_8005C718[i].unk_04 * 2;
        D_8005C718[i].unk_18 = func_8000B924(size * D_8005C718[i].unk_08);
        func_80021B4C(D_8005C718[i].unk_1C, D_8005C718[i].unk_08, D_8005C718[i].unk_18, D_8005C718[i].unk_20);
    }
    D_800B96AC = 0;
}
