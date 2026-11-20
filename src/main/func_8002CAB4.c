#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u8 unk_08[0x4];
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u8 unk_10[0x18];
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ u8 unk_30[0x4];
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ u8 unk_38[0x18];
} Entry;

extern Entry D_8005A4C8[];
extern s32 D_800FB808;

void func_8002CAB4(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        D_8005A4C8[i].unk_00 = i == D_800FB808;
        D_8005A4C8[i].unk_0C = D_8005A4C8[i].unk_04;
        D_8005A4C8[i].unk_28 = i == D_800FB808;
        D_8005A4C8[i].unk_34 = D_8005A4C8[i].unk_2C;
    }
}
