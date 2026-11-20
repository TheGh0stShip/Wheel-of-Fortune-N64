#include "wof.h"

s32 func_8000A4A4(proc_t *proc, s32 arg1) {
    proc_t *prev;
    proc_t *next;

    prev = func_8000A158(proc);
    if (prev == 0) {
        return 0;
    }
    next = proc->next;
    prev->next = next;
    D_800BEE50--;
    proc->unk_00 = 0;
    func_8000A408(proc->unk_04);
    if (arg1 != 0) {
        func_8000B2D4(proc->unk_04);
    }
    return 1;
}
