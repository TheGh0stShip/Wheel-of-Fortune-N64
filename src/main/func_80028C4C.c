#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
} Inner;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ Inner *unk_30;
} Outer;

extern s32 D_800B9CF8;
extern s32 D_800B9CFC;

void func_80028C4C(Outer *arg0) {
    arg0->unk_30->unk_04 = 2;
    if (D_800B9CF8 != 0) {
        arg0->unk_30->unk_04 = 0;
        return;
    }
    if (D_800B9CFC != 0) {
        arg0->unk_30->unk_04 = 1;
    }
}
