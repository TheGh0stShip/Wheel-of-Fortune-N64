#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x44];
    /* 0x44 */ s32 unk_44;
} Inner;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ Inner **unk_30;
} Obj;

typedef struct {
    /* 0x00000 */ u8 unk_00000[0x4];
    /* 0x00004 */ u8 unk_04[0x1E47C];
} Frame;

extern Frame D_800BEF5C[];
extern s32 D_800B40C4;
extern s32 D_800B61A0;
extern u8 D_800BEF60[][0x1E480];

void func_800212C0(s32 arg0) {
    s32 diff;
    s32 pad0;
    s32 pad1[6];
    s32 pad2;
    s32 base;

    base = 0x2000000;
    diff = func_8003FF78(D_800BEF5C[D_800B61A0].unk_04 + 0x19C00);
    diff = diff - func_8003FF78(D_800BEF60[D_800B61A0]);
    (*((Obj *)arg0)->unk_30)->unk_44 = base + diff;
    if (D_800B40C4 == 0) {
        D_800B40C4 = func_8009D244();
    }
}
