#include "wof.h"

struct n64dk_r12 { s32 w[3]; };

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
    /* 0x00 */ u8 unk_00[0x10];
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ u8 unk_16[0x36];
    /* 0x4C */ s32 unk_4C;
} Object;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u8 unk_0C[0x4];
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ u8 unk_14[0x10];
} Entry;

extern Entry D_8005C720[];
extern s32 D_0113A9B0;
extern s32 D_0113A9D0;
extern s32 D_80001974;
void func_80009F38(s32 *arg0);
s32 func_8000A4A4(s32 arg0, s32 arg1);
s32 func_8000A56C(s32 arg0, s32 arg1);
s32 func_8000A990(s32 arg0, s32 arg1);
s32 func_80015848(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_80030490(s32 arg0, s32 arg1);
struct n64dk_r12 func_800315FC(s32 arg1);

void func_800323C4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Task *task;
    Object *obj;

    if (arg0 < 0) {
        return;
    }
    if (arg0 >= 6) {
        func_80009F38(&D_80001974);
    }
    if (D_8005C720[arg0].unk_10 == 0) {
        return;
    }
    task = (Task *)func_8000A990(arg1 | 0xA000300, -1);
    if (task != 0) {
        func_8000A4A4((s32)task, 0);
    }
    task = (Task *)func_8000A56C((s32)func_800315FC, arg1 | 0xA000300);
    obj = (Object *)func_80015848((s32)task, (s32)&D_0113A9B0, (s32)func_80030490, arg1 | 0xA020000);
    obj->unk_4C = (s32)&D_0113A9D0;
    obj->unk_10 = arg2;
    obj->unk_12 = arg3;
    obj->unk_14 = arg4;
    task->data->unk_04 = arg1;
    task->data->unk_08 = D_8005C720[arg0].unk_10;
    task->data->unk_18 = D_8005C720[arg0].unk_00;
    task->data->unk_1C = D_8005C720[arg0].unk_08;
    task->data->unk_00 = (s32)obj;
}
