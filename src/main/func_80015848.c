#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u8 unk_08[0x8];
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ u8 unk_1C[0xC];
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 *unk_30;
    /* 0x34 */ u8 unk_34[0x14];
    /* 0x48 */ s32 unk_48;
} Obj;

extern f32 D_80000D0C;

s32 func_80015848(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Obj *obj;
    s32 parent;

    parent = 0;
    if (arg0 != 0) {
        parent = ((Obj *)arg0)->unk_04;
    }
    obj = (Obj *)func_8000B3B0(parent, arg2, arg3);
    if (obj == 0) {
        return (s32)obj;
    }
    if (arg0 != 0) {
        *((Obj *)arg0)->unk_30 = (s32)obj;
    }
    obj->unk_18 = D_80000D0C;
    obj->unk_10 = 0;
    obj->unk_12 = 0;
    obj->unk_14 = 0;
    obj->unk_28 = 0;
    obj->unk_2C = 0;
    obj->unk_30 = 0;
    obj->unk_48 = arg1;
    return (s32)obj;
}
