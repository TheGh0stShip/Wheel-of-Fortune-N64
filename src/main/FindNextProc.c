#include "wof.h"

proc_t *FindNextProc(proc_t *proc, s32 cls, s32 mask) {
    while (proc->next != 0) {
        proc = proc->next;
        if ((proc->unk_08 & mask) == cls) {
            return proc;
        }
    }
    return 0;
}
