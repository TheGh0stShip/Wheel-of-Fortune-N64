#include "wof.h"

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
    proc->unk_00 = 0;
    FreeBlocks(proc->unk_04);
    if (killObjs != 0) {
        FreeProcObjs(proc->unk_04);
    }
    return 1;
}
