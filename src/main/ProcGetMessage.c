#include "wof.h"


/*
=====================
ProcGetMessage

Takes the last message queued for a proc, or 0 if none.
=====================
*/
s32 ProcGetMessage(proc_t *proc) {
    if (proc == 0) {
        func_80009F38("ProcGetMessage: NULL proc\n");
        return 0;
    }
    if (proc->count != 0) {
        proc->count--;
        return proc->items[proc->count];
    }
    return 0;
}
