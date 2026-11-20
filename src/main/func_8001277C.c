#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0xC];
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
} Timer;

extern s32 D_800B96B4;

s32 func_8001277C(Timer *arg0) {
    s32 result;

    result = arg0->unk_18;
    if (arg0->unk_0C != 0) {
        if (arg0->unk_14 > arg0->unk_10 / 2) {
            result = -1;
        }
        arg0->unk_14 = arg0->unk_14 - D_800B96B4;
        if (arg0->unk_14 < 0) {
            arg0->unk_14 = arg0->unk_10;
        }
    }
    return result;
}
