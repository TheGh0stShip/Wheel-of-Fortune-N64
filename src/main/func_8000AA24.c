#include "wof.h"

proc_t *func_8000AA24(proc_t *proc, s32 arg1, s32 arg2) {
    while (proc->next != 0) {
        proc = proc->next;
        if ((proc->unk_08 & arg2) == arg1) {
            return proc;
        }
    }
    return 0;
}
