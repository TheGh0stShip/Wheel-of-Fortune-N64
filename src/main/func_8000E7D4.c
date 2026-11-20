#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
} Data;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ Data *data;
} Task;

typedef struct {
    /* 0x00 */ u8 unk_00[0x10];
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ u8 unk_16[0x12];
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ u8 unk_34[0x8];
    /* 0x3C */ s32 unk_3C;
} Obj;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u8 unk_08[0x4];
} Entry;

extern Entry D_80057808[];

void func_8000E7D4(void) {
    Task *task;
    Obj *obj;
    s32 pad0;
    s32 i;

    D_800FB808 = 0;
    D_800BCD54 = 1;
    func_800174DC();
    func_80016B9C(6);
    D_800B3994 = 0;
    func_80015848(0, 0, (s32)func_8000CB58, 0x8000000);
    func_80015848(0, 0, (s32)func_8000DCA0, 0x8000000);
    for (i = 0; i < 14; i++) {
        task = (Task *)func_8000A56C((s32)func_8000C6C4, 0x8010000);
        task->data->unk_08 = i;
        obj = (Obj *)func_80015848((s32)task, D_80057808[i].unk_00, (s32)func_8000D6D8, 0x8010000);
        obj->unk_3C = D_80057808[i].unk_04;
    }
    task = (Task *)func_8000A56C((s32)func_8000C310, 0x8010000);
    obj = (Obj *)func_80015848((s32)task, (s32)&D_011356C0, (s32)func_8000D8B8, 0x8010000);
    obj->unk_12 = -20;
    task = (Task *)func_8000A56C((s32)func_8000BEA8, 0x8000000);
    obj = (Obj *)func_80015848((s32)task, (s32)&D_01197D78, (s32)func_8000D400, 0x8010000);
    task->data->unk_0C = -272.0f;
    task->data->unk_10 = 306.0f;
    task->data->unk_14 = -411.0f;
    obj->unk_10 = -272;
    obj->unk_12 = 306;
    obj->unk_14 = -411;
    obj->unk_28 = -61.317f;
    obj->unk_2C = 58.385f;
    obj->unk_30 = -9.848f;
    D_800B61AC = 0;
    task->data->unk_04 = func_80002CE0(15);
    for (i = 0; i < 24; i++) {
        task = (Task *)func_8000A56C((s32)func_8000C50C, 0x8010000);
        task->data->unk_08 = i;
        obj = (Obj *)func_80015848((s32)task, D_800578B0[i], (s32)func_8000D6D8, 0x8010000);
        obj->unk_3C = D_80057910[i];
    }
    func_80015848(0, 0, (s32)func_800287A4, 0x5000000);
    D_800B6198 = 721;
    D_800BEE24 = 0;
}
