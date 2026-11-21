#include "wof.h"


/*
=====================
ProcClearMessages

Drops every message queued for a proc.
=====================
*/
void ProcClearMessages(proc_t *proc) {
    if (proc == 0) {
        func_80009F38("ProcClearMessages: NULL proc\n");
    }
    proc->count = 0;
}
