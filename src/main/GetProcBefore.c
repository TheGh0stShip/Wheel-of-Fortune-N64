// GetProcBefore.c -- the proc before one in the list of live procs; the list's head if it is the
// first

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
