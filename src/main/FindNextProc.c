// FindNextProc.c -- the next such proc after one

#include "wof.h"

/*
=====================
FindNextProc

The next such proc after one.
=====================
*/
proc_t *FindNextProc(proc_t *proc, s32 cls, s32 mask) {
    while (proc->next != 0) {
        proc = proc->next;
        if ((proc->cls & mask) == cls) {
            return proc;
        }
    }
    return 0;
}
