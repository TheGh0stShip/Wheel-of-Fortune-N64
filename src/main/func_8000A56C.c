#include "wof.h"


s32 func_8000A56C(s32 arg0, s32 arg1) {
    proc_t *last;
    proc_t *task;
    s8 pad0;

    last = (proc_t *)func_8000A0E4();
    task = (proc_t *)func_8000A204();
    if (task == 0) {
        func_80009F38("CreatProc: Failed to alloc proc\n");
        return 0;
    }
    last->next = (s32)task;
    task->unk_00 = arg0;
    task->unk_08 = arg1;
    task->unk_0C = 0;
    task->unk_10 = 0;
    task->items[0] = 8;
    task->count = 1;
    task->next = 0;
    task->unk_34 = 0;
    task->unk_38 = 0;
    task->unk_30 = func_8000A31C(task->unk_04);
    return (s32)task;
}
