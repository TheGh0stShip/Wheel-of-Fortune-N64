#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u8 unk_08[0x4];
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ u8 unk_18[0x4];
} Entry;

extern s32 D_010A2B88;

void func_80015EDC(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 i;

    for (i = 0; i < arg3; i++) {
        ((Entry *)arg1)[i].unk_00 = ((s32 *)arg0)[i];
        ((Entry *)arg1)[i].unk_0C = 0;
        ((Entry *)arg1)[i].unk_10 = 32;
        ((Entry *)arg1)[i].unk_14 = 0;
        ((Entry *)arg1)[i].unk_04 = (s32)&D_010A2B88;
    }
}
