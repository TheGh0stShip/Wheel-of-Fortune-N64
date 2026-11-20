#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u8 unk_08[0x4];
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u8 unk_10[0x44];
} Entry;

extern Entry D_800B40C8[];

void func_8000AF00(void) {
    s32 i;

    for (i = 0; i < 100; i++) {
        D_800B40C8[i].unk_0C = 0;
        D_800B40C8[i].unk_00 = i;
        D_800B40C8[i].unk_04 = 0;
    }
    D_800BCA10 = 0;
    D_800B40D4 = 0;
    D_800B4118 = 0;
}
