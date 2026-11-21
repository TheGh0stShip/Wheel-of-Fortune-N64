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
        func_80009F38("AllocProc: Out of Procs\n");
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
    func_80009F38("AllocProc: Reached end of procst.\n");
    return 0;
}
