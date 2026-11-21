#include "wof.h"

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
