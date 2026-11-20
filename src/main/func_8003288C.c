#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u8 unk_10[0x4];
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
} State;

typedef struct {
    /* 0x00 */ u8 unk_00[0x10];
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ u8 unk_12[0x1E];
    /* 0x30 */ State *state;
} Task;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ u8 unk_14[0x10];
} Entry;

extern Entry D_8005C7F8[];

s32 func_8003288C(s32 arg0, s32 arg1) {
    Task *task;
    Task *child;
    s32 id;

    id = arg0;
    if (arg0 < 0) {
        return;
    }
    if (arg0 == 80) {
        arg0 = 2;
    } else if (arg0 >= 6) {
        func_80009F38("InitVannaAnim: invalid animation number");
    }
    if (D_8005C7F8[arg0].unk_10 == 0) {
        return 0;
    }
    if (arg1 != 0) {
        func_8000AE70(0xA000400, -1, 1);
        func_8000B6FC(0xA030000, -1);
    }
    task = (Task *)func_8000A56C((s32)&func_80031A54, 0xA000400);
    child = (Task *)func_80015848((s32)task, 0, (s32)&func_80030B5C, 0xA030000);
    child->unk_10 = D_800B998A;
    task->state->unk_0C = id;
    task->state->unk_08 = D_8005C7F8[arg0].unk_10;
    task->state->unk_18 = D_8005C7F8[arg0].unk_00;
    task->state->unk_14 = D_8005C7F8[arg0].unk_04;
    task->state->unk_1C = D_8005C7F8[arg0].unk_08;
    task->state->unk_20 = D_8005C7F8[arg0].unk_0C;
    task->state->unk_00 = (s32)child;
    return (s32)task;
}
