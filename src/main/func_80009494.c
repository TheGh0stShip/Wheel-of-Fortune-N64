#include "wof.h"

typedef struct {
    u8 unk_00[0x14];
} Entry;

extern s32 D_800007D0;
extern s32 D_800B9990;
extern s32 D_800B9994;
extern Entry D_800B99C0[];
extern s32 D_800B9A88;
extern s32 D_800B9AA4;
extern s32 D_800B9AA8;
extern Entry D_800B9AD4[];
extern s32 D_800B9B9C;
extern s32 D_800B9BB8;
extern s32 D_800B9BBC;
extern Entry D_800B9BE8[];
extern s32 D_800B9CB0;

void func_80009494(void) {
    s32 i;

    D_800B9990 = 0;
    D_800B9994 = 0;
    D_800B9A88 = 0;
    for (i = 0; i < 10; i++) {
        func_80009900((s32)&D_800B99C0[i], (s32)&D_800007D0);
    }
    D_800B9AA4 = 0;
    D_800B9AA8 = 0;
    D_800B9B9C = 0;
    for (i = 0; i < 10; i++) {
        func_80009900((s32)&D_800B9AD4[i], (s32)&D_800007D0);
    }
    D_800B9BB8 = 0;
    D_800B9BBC = 0;
    D_800B9CB0 = 0;
    for (i = 0; i < 10; i++) {
        func_80009900((s32)&D_800B9BE8[i], (s32)&D_800007D0);
    }
}
