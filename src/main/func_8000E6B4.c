#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ s32 *unk_30;
} Task;

extern s32 func_8000E4B0;
extern s32 func_800288CC;
extern s32 D_800BCD54;
void func_80005700(void);
s32 func_8000A56C(s32 arg0, s32 arg1);
s32 func_80015848(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_8000E6B4(void) {
    Task *task;
    s32 sp14;

    D_800BCD54 = 1;
    func_80005700();
    sp14 = func_80015848(0, 0, (s32)&func_800288CC, 0x5030000);
    task = (Task *)func_8000A56C((s32)&func_8000E4B0, 0x8010000);
    *task->unk_30 = sp14;
}
