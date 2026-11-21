// CreatProc.c -- makes a proc with a handler and a class, links it at the end of the list, gives it
// a data block and the start message (8)

#include "wof.h"


/*
=====================
CreatProc

Makes a proc with a handler and a class, links it at the end of the list, gives it a data block and
the start message (8).
=====================
*/
proc_t *CreatProc(procHandler_t handler, s32 cls) {
    proc_t *last;
    proc_t *task;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    last = GetLastProc();
    task = AllocProc();
    if (task == 0) {
        FatalError("CreatProc: Failed to alloc proc\n");
        return 0;
    }
    last->next = task;
    task->handler = handler;
    task->cls = cls;
    task->sleep = 0;
    task->event = 0;
    task->items[0] = 8;
    task->count = 1;
    task->next = 0;
    task->unk_34 = 0;
    task->unk_38 = 0;
    task->data = AllocBlock(task->id);
    return task;
}
