#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x8];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
} Data;

typedef struct {
    /* 0x00 */ u8 unk_00[0x10];
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ u8 unk_1C[0xC];
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ union {
        f32 unk_30;
        Data *data;
    } u;
    /* 0x34 */ u8 unk_34[0x14];
    /* 0x48 */ s32 unk_48;
} Obj;

typedef struct {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u8 unk_02[0x2];
    /* 0x04 */ u16 unk_04;
    /* 0x06 */ u8 unk_06[0x2];
    /* 0x08 */ u16 unk_08;
    /* 0x0A */ u8 unk_0A[0x16];
} Angles;

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ u8 unk_14[0xC];
} Pose;

extern Angles D_80057F52[];
extern Pose D_80057F5C[];
extern f32 D_80000E88;
extern f32 D_800B6BE8;
extern f32 D_800B6BEC;
extern f32 D_800B6BF0;
extern s32 D_800BA2BC;
extern s32 D_800BA5D8;

void func_80016944(s32 arg0, s32 arg1) {
    s32 task;

    D_800BA2BC = arg1;
    ((Obj *)arg0)->unk_18 = D_80000E88;
    ((Obj *)arg0)->unk_10 = D_80057F52[arg1].unk_00;
    ((Obj *)arg0)->unk_12 = D_80057F52[arg1].unk_04;
    ((Obj *)arg0)->unk_14 = D_80057F52[arg1].unk_08;
    ((Obj *)arg0)->unk_28 = D_80057F5C[arg1].unk_00;
    ((Obj *)arg0)->unk_2C = D_80057F5C[arg1].unk_04;
    ((Obj *)arg0)->u.unk_30 = D_80057F5C[arg1].unk_08;
    ((Obj *)arg0)->unk_48 = 0;
    task = func_8000A990(0x3010000, -1);
    if (task != 0) {
        func_8000A4A4(task, 0);
    }
    if (D_80057F5C[arg1].unk_0C != 0) {
        task = func_8000A56C((s32)func_80016734, 0x3010000);
        ((Obj *)task)->u.data->unk_08 = D_80057F5C[arg1].unk_0C;
        ((Obj *)task)->u.data->unk_0C = 0;
        ((Obj *)task)->u.data->unk_10 = D_80057F5C[arg1].unk_10;
        D_800B6BE8 = D_80057F5C[arg1].unk_00;
        D_800B6BEC = D_80057F5C[arg1].unk_04;
        D_800B6BF0 = D_80057F5C[arg1].unk_08;
        return;
    }
    D_800BA5D8 = 0;
    D_800B6BE8 = 0;
    D_800B6BEC = 0;
    D_800B6BF0 = 0;
}
