// wof_procevent.c -- posting an event, finding procs by class and posting a message to one proc
//
// FindProc ends off an 8-byte boundary with FindNextProc right after, which happens only inside an
// object, and ProcPostEvent's read-only items run on into ProcPostMessage's with no 8-byte boundary
// between: ProcPostEvent to ProcPostMessage are one object's. Whether DoProcs before it and
// ProcPostMessageClass after it are this object's the text does not say.

#include "wof.h"

/*
=====================
ProcPostEvent

Gives an event to every proc that waits for it, or for any, as a message, and wakes it.
=====================
*/
void ProcPostEvent(s32 event) {
    struct procResult_s unused;  /* NOTE: unused in the original; DoProcs uses its own */
    proc_t *node;

    if (event >= 53) {
        FatalError("ProcPostEvent: bogus event\n");
        return;
    }
    node = &procst[0];
    while (node->next != 0) {
        node = node->next;
        if (node->event == event || node->event == -1) {
            node->event = 0;
            node->waiting = 0;
            node->sleep = 0;
            if (node->count < 5) {
                node->items[node->count] = event;
                node->count++;
            } else {
                FatalError("ProcPostEvent: Message Que overrun.\n");
            }
        }
    }
}

/*
=====================
FindProc

The first proc whose class under a mask is a value.
=====================
*/
proc_t *FindProc(s32 cls, s32 mask) {
    proc_t *node;

    node = &procst[0];
    while (node->next != 0) {
        node = node->next;
        if ((node->cls & mask) == cls) {
            return node;
        }
    }
    return 0;
}

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
