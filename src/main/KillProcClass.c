// KillProcClass.c -- kills every proc of a class

#include "wof.h"

/*
=====================
KillProcClass

Kills every proc of a class.
=====================
*/
void KillProcClass(s32 cls, s32 mask, s32 killObjs) {
    proc_t *proc;

    proc = FindProc(cls, mask);
    while (proc != 0) {
        KillProc(proc, killObjs);
        proc = FindNextProc(proc, cls, mask);
    }
}
