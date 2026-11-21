// wof_procalloc.c -- the proc before another, a free proc and a free data block
//
// GetProcBefore and AllocProc each end off an 8-byte boundary with the next function right after, which
// happens only inside an object. Whether GetLastProc before it and FreeBlocks after it are this
// object's the text does not say.

#include "wof.h"

/*
=====================
GetProcBefore

The proc before one in the list of live procs; the list's head if it is the first.
=====================
*/
proc_t *GetProcBefore(proc_t *proc) {
    proc_t *cur;
    proc_t *prev;

    prev = &procst[0];
    cur = prev->next;
    while (cur != 0) {
        if (cur == proc) {
            return prev;
        }
        prev = cur;
        cur = prev->next;
    }
    FatalError("GetProcBefore: Could not find proc\n");
    return 0;
}

/*
=====================
AllocProc

A free entry of procst, or 0 when none is left.
=====================
*/
proc_t *AllocProc(void) {
    s32 i;

    if (numProcs == 69) {
        FatalError("AllocProc: Out of Procs\n");
        return 0;
    }
    i = 1;
    while (i < 70) {
        if (procst[i].handler == 0) {
            numProcs++;
            return &procst[i];
        }
        i++;
    }
    FatalError("AllocProc: Reached end of procst.\n");
    return 0;
}

/*
=====================
AllocBlock

A free data block of 0x50 bytes for a proc, which it then owns.
=====================
*/
void *AllocBlock(s32 owner) {
    s32 i;

    for (i = 0; i < 70; i++) {
        if (blockOwners[i] == 0) {
            blockOwners[i] = owner;
            return blocks[i];
        }
    }
    FatalError("AllocBlock: Out of Blocks.\n");
    return 0;
}
