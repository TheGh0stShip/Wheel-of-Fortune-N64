// wof_procrun.c -- freeing a proc's blocks, killing and making procs, and running them each frame
//
// FreeBlocks, KillProc and CreatProc each end off an 8-byte boundary with the next function right
// after, which happens only inside an object. Whether AllocBlock before it and ProcPostEvent after it
// are this object's the text does not say.

#include "wof.h"

/*
=====================
FreeBlocks

Frees the data blocks a proc owns.
=====================
*/
void FreeBlocks(s32 owner) {
    s32 i;

    for (i = 0; i < 70; i++) {
        if (blockOwners[i] == owner) {
            blockOwners[i] = 0;
        }
    }
}

/*
=====================
KillProc

Unlinks a proc and frees its blocks, and its objs if asked.
=====================
*/
s32 KillProc(proc_t *proc, s32 killObjs) {
    proc_t *prev;
    proc_t *next;

    prev = GetProcBefore(proc);
    if (prev == 0) {
        return 0;
    }
    next = proc->next;
    prev->next = next;
    numProcs--;
    proc->handler = 0;
    FreeBlocks(proc->id);
    if (killObjs != 0) {
        FreeProcObjs(proc->id);
    }
    return 1;
}

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
    task->creatZero1 = 0;
    task->creatZero2 = 0;
    task->data = AllocBlock(task->id);
    return task;
}

/*
=====================
DoProcs

Runs each live proc's handler once a frame, unless it sleeps or waits, and acts on what the handler
returns. While the game is paused only the pause proc runs.
=====================
*/
void DoProcs(void) {
    struct procResult_s res;
    proc_t *task;

    task = &procst[0];
    while (task->next != 0) {
        task = task->next;
        if (task->handler == 0) {
            FatalError("DoProcs: Tried to execute a NULL\n");
            return;
        }
        if (task->waiting == 0) {
            if (task->sleep > 0) {
                if (gameMode != 6) {
                    task->sleep--;
                }
            } else {
                if (gameMode == 6) {
                    if (task->cls == 0xB000000) {
                        res = task->handler(task);
                    }
                } else {
                    res = task->handler(task);
                }
                switch (res.w[1]) {
                case 0:
                    KillProc(task, res.w[0]);
                    break;
                case 1:
                    task->sleep = res.w[0];
                    break;
                case 2:
                    task->event = res.w[0];
                    task->waiting = 1;
                    break;
                case 3:
                    task->event = res.w[0];
                    break;
                }
            }
        }
    }
}
