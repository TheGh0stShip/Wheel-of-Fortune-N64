// ProcClearMessages.c -- drops every message queued for a proc

#include "wof.h"


/*
=====================
ProcClearMessages

Drops every message queued for a proc.
=====================
*/
void ProcClearMessages(proc_t *proc) {
    if (proc == 0) {
        FatalError("ProcClearMessages: NULL proc\n");
    }
    proc->count = 0;
}
