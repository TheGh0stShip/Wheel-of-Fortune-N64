// AllocProc.c -- a free entry of procst, or 0 when none is left

#include "wof.h"

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
