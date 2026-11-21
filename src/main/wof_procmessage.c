// wof_procmessage.c -- messages to a class of procs, taking and dropping a proc's messages, and
// killing every proc but one
//
// ProcGetMessage and ProcClearMessages each end off an 8-byte boundary with the next function right
// after, which happens only inside an object, and ProcPostMessageClass's read-only items run on into
// ProcGetMessage's with no 8-byte boundary between. Whether ProcPostMessage before it and
// KillProcClass after it are this object's the text does not say.

#include "wof.h"

/*
=====================
ProcPostMessageClass

ProcPostMessage to every proc of a class.
=====================
*/
void ProcPostMessageClass(s32 msg, s32 cls, s32 mask, s32 wake) {
    proc_t *node;

    node = FindProc(cls, mask);
    while (node != 0) {
        if (msg >= 53) {
            FatalError("ProcPostMessageClass: bogus message\n");
            return;
        }
        if (node->count < 5) {
            node->items[node->count] = msg;
            node->count++;
        } else {
            FatalError("ProcPostMessageClass: Message Que overrun.\n");
        }
        if (wake != 0) {
            node->waiting = 0;
            node->sleep = 0;
        }
        node = FindNextProc(node, cls, mask);
    }
}

/*
=====================
ProcGetMessage

Takes the last message queued for a proc, or 0 if none.
=====================
*/
s32 ProcGetMessage(proc_t *proc) {
    if (proc == 0) {
        FatalError("ProcGetMessage: NULL proc\n");
        return 0;
    }
    if (proc->count != 0) {
        proc->count--;
        return proc->items[proc->count];
    }
    return 0;
}

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

/*
=====================
KillOtherProcs

Kills every proc but one.
=====================
*/
void KillOtherProcs(proc_t *proc) {
    struct procResult_s res;
    proc_t *node;

    node = &procst[0];
    while (node->next != 0) {
        node = node->next;
        if (node != proc) {
            KillProc(node, res.w[0]);  // BUG: res is never set
        }
    }
}
