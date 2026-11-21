// ProcPostMessage.c -- queues a message for a proc, and wakes it if asked

#include "wof.h"


/*
=====================
ProcPostMessage

Queues a message for a proc, and wakes it if asked.
=====================
*/
void ProcPostMessage(proc_t *proc, s32 msg, s32 wake) {
    if (proc == 0) {
        FatalError("ProcPostMessage: NULL proc\n");
        return;
    }
    if (msg >= 53) {
        FatalError("ProcPostMessage: bogus message\n");
        return;
    }
    if (proc->count < 5) {
        proc->items[proc->count] = msg;
        proc->count++;
        if (wake != 0) {
            proc->waiting = 0;
            proc->sleep = 0;
        }
        return;
    }
    FatalError("ProcPostMessage: Message Que overrun.\n");
}
