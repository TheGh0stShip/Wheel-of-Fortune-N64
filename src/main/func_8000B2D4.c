#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u8 unk_08[0x4C];
} Entry;

extern Entry D_800B40C8[];

void func_8000B2D4(s32 arg0) {
    s32 i;
    s32 result;

    for (i = 0; i < 100; i++) {
        if (D_800B40C8[i].unk_04 == arg0) {
            result = func_8000B234((s32)&D_800B40C8[i]);
            if (result == 1) {
            }
        }
    }
}
