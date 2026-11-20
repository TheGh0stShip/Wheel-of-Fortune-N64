#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ u8 unk_14[0x4];
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ u8 unk_20[0x10];
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ u8 unk_3C[0x4];
    /* 0x40 */ s32 unk_40;
} Task;

extern s32 D_80000870;

s32 func_8000A56C(s32 arg0, s32 arg1) {
    Task *last;
    Task *task;
    s8 pad0;

    last = (Task *)func_8000A0E4();
    task = (Task *)func_8000A204();
    if (task == 0) {
        func_80009F38(&D_80000870);
        return 0;
    }
    last->unk_40 = (s32)task;
    task->unk_00 = arg0;
    task->unk_08 = arg1;
    task->unk_0C = 0;
    task->unk_10 = 0;
    task->unk_1C = 8;
    task->unk_18 = 1;
    task->unk_40 = 0;
    task->unk_34 = 0;
    task->unk_38 = 0;
    task->unk_30 = func_8000A31C(task->unk_04);
    return (s32)task;
}
