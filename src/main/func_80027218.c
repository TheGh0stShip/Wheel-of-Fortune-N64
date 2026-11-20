#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x10];
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ u8 unk_1C[0xC];
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ u8 unk_34[0x14];
    /* 0x48 */ s32 unk_48;
} Obj;

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u8 unk_08[0x28];
    /* 0x30 */ Obj **unk_30;
} Task;

extern f32 D_8000168C;
s32 func_8000B3B0(s32 arg0, s32 arg1, s32 arg2);

s32 func_80027218(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Obj *obj;
    s32 sp14;

    sp14 = 0;
    if (arg0 != 0) {
        sp14 = ((Task *)arg0)->unk_04;
    }
    obj = (Obj *)func_8000B3B0(sp14, arg2, arg3);
    if (obj == 0) {
        return (s32)obj;
    }
    if (arg0 != 0) {
        *((Task *)arg0)->unk_30 = obj;
    }
    obj->unk_18 = D_8000168C;
    obj->unk_10 = -160;
    obj->unk_12 = -80;
    obj->unk_14 = -450;
    obj->unk_28 = 0;
    obj->unk_2C = 0;
    obj->unk_30 = 0;
    obj->unk_48 = arg1;
    return (s32)obj;
}
