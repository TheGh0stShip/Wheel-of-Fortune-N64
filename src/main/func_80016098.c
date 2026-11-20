#include "wof.h"

void func_80016098(void) {
    proc_t *task;
    s32 sp14;

    sp14 = func_8000B5DC(0xA010100, -1);
    if (sp14 != 0) {
        task = (proc_t *)func_8000A990(0xA010100, -1);
        if (task == 0) {
            task = (proc_t *)func_8000A56C((s32)&func_800101F4, 0xA010100);
            *(s32 *)task->unk_30 = sp14;
        }
    }
    sp14 = func_8000B5DC(0xA010200, -1);
    if (sp14 != 0) {
        task = (proc_t *)func_8000A990(0xA010200, -1);
        if (task == 0) {
            task = (proc_t *)func_8000A56C((s32)&func_800103B4, 0xA010200);
            *(s32 *)task->unk_30 = sp14;
        }
    }
}
