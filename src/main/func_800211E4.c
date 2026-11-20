#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
} Parent;

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
} Task;

extern f32 D_80001558;
extern s32 func_80020150;
s32 func_8000B3B0(s32 arg0, s32 arg1, s32 arg2);

s32 func_800211E4(s32 arg0, s32 arg1, f32 arg2, f32 arg3) {
    s32 parent;
    Task *task;

    parent = 0;
    if (arg0 != 0) {
        parent = ((Parent *)arg0)->unk_04;
    }
    task = (Task *)func_8000B3B0(parent, (s32)&func_80020150, 0x5010000);
    task->unk_18 = D_80001558;
    task->unk_10 = arg2;
    task->unk_12 = arg3;
    task->unk_14 = 0;
    task->unk_28 = 0;
    task->unk_2C = 0;
    task->unk_30 = 0;
    task->unk_48 = 0;
    return (s32)task;
}
