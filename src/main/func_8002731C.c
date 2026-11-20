#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x10];
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
} Timer;

s32 func_8002731C(s32 arg0, s32 arg1) {
    s32 result;

    if (arg1 != 0) {
        result = ((Timer *)arg0)->unk_20;
    } else {
        result = ((Timer *)arg0)->unk_24;
    }
    if (((Timer *)arg0)->unk_10 == 1) {
        if (((Timer *)arg0)->unk_1C > ((Timer *)arg0)->unk_18) {
            result = ((Timer *)arg0)->unk_24;
        }
        ((Timer *)arg0)->unk_1C -= D_800B96B4;
        if (((Timer *)arg0)->unk_1C < 0) {
            ((Timer *)arg0)->unk_1C = ((Timer *)arg0)->unk_14;
        }
    } else if (((Timer *)arg0)->unk_10 == 2) {
        result = ((Timer *)arg0)->unk_24;
    }
    return result;
}
