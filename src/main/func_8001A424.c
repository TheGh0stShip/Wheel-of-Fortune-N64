#include "wof.h"

void func_8001A424(s32 arg0) {
    proc_t *task;
    s32 pad0;
    s8 pad1;

    task = (proc_t *)func_8000A56C((s32)func_80019AAC, arg0 | 0x2020000);
    ((data80019AAC_t *)task->unk_30)->player = arg0;
}
