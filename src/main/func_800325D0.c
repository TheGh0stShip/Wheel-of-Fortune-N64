#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u8 unk_0C[0xC];
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
} TaskData;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ TaskData *data;
} Task;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u8 unk_0C[0x4];
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ u8 unk_14[0x10];
} Entry;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x110];
} Player;

extern Entry D_8005C3C0[][2];
extern Player D_800B99A8[];
extern s32 D_80001974;
extern s32 D_80001998;
extern s32 D_800019BC;

void func_800325D0(s32 arg0, s32 arg1) {
    Task *task;
    s32 obj;
    s32 kind;

    if (arg0 < 0) {
        return;
    }
    if (arg0 >= 2) {
        func_80009F38(&D_80001974);
    }
    kind = D_800B99A8[arg1].unk_00;
    if (kind >= 6) {
        func_80009F38(&D_80001998);
    }
    if (D_8005C3C0[kind][arg0].unk_10 == 0) {
        return;
    }
    obj = func_8000B5DC(arg1 | 0xA020000, -1);
    if (obj == 0) {
        func_80009F38(&D_800019BC);
    }
    task = (Task *)func_8000A990(arg1 | 0xA000300, -1);
    if (task != 0) {
        func_8000A4A4((s32)task, 0);
    }
    task = (Task *)func_8000A56C((s32)func_800315FC, arg1 | 0xA000300);
    task->data->unk_04 = arg1;
    task->data->unk_08 = D_8005C3C0[kind][arg0].unk_10;
    task->data->unk_18 = D_8005C3C0[kind][arg0].unk_00;
    task->data->unk_1C = D_8005C3C0[kind][arg0].unk_08;
    task->data->unk_00 = obj;
}
