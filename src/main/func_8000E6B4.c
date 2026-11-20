#include "wof.h"

void func_8000E6B4(void) {
    proc_t *task;
    s32 sp14;

    D_800BCD54 = 1;
    func_80005700();
    sp14 = func_80015848(0, 0, (s32)&func_800288CC, 0x5030000);
    task = (proc_t *)func_8000A56C((s32)&func_8000E4B0, 0x8010000);
    *(s32 *)task->unk_30 = sp14;
}
