// wof_proc.c -- the procs: clearing them, the list and its free entries and blocks, making, killing and
// running procs, their events and messages, and finding and killing them by class
//
// The object lies between the 4-byte gaps that end PrintStr and KillProcClass. InitProcs, GetProcBefore,
// AllocProc, FreeBlocks, KillProc, CreatProc, FindProc, ProcGetMessage and ProcClearMessages each end off
// an 8-byte boundary with the next function right after, which happens only inside an object;
// ProcPostEvent's read-only items run on into ProcPostMessage's, and ProcPostMessageClass's into
// ProcGetMessage's, with no 8-byte boundary between. guess: the joins after GetLastProc, AllocBlock,
// DoProcs, ProcPostMessage and KillOtherProcs. The zero word before 0x800007F0 opens the read-only data
// of an object starting after PrintStr or GetLastProc; the gap after PrintStr is one of them and an
// object starts there for certain, so the start takes it, and the project's ruling takes the join
// everywhere else.

#include "wof.h"

/*
=====================
InitProcs

Clears procst and the data block owners.
=====================
*/
void InitProcs(void) {
    s32 i;

    for (i = 0; i < 70; i++) {
        procst[i].handler = 0;
        procst[i].id = i;
    }
    numProcs = 0;
    procst[0].handler = 0;
    procst[0].next = 0;
    initProcsZero = 0;
    for (i = 0; i < 70; i++) {
        blockOwners[i] = 0;
    }
}

/*
=====================
GetLastProc

The last proc of the list, after which CreatProc links a new one; named after GetProcBefore.
=====================
*/
proc_t *GetLastProc(void) {
    proc_t *next;
    proc_t *node;

    node = &procst[0];
    next = node->next;
    while (next != 0) {
        node = next;
        next = node->next;
    }
    return node;
}

/*
=====================
GetProcBefore

The proc before one in the list of live procs; the list's head if it is the first.
=====================
*/
proc_t *GetProcBefore(proc_t *proc) {
    proc_t *cur;
    proc_t *prev;

    prev = &procst[0];
    cur = prev->next;
    while (cur != 0) {
        if (cur == proc) {
            return prev;
        }
        prev = cur;
        cur = prev->next;
    }
    FatalError("GetProcBefore: Could not find proc\n");
    return 0;
}

/*
=====================
AllocProc

A free entry of procst, or 0 when none is left.
=====================
*/
proc_t *AllocProc(void) {
    s32 i;

    if (numProcs == 69) {
        FatalError("AllocProc: Out of Procs\n");
        return 0;
    }
    i = 1;
    while (i < 70) {
        if (procst[i].handler == 0) {
            numProcs++;
            return &procst[i];
        }
        i++;
    }
    FatalError("AllocProc: Reached end of procst.\n");
    return 0;
}

/*
=====================
AllocBlock

A free data block of 0x50 bytes for a proc, which it then owns.
=====================
*/
void *AllocBlock(s32 owner) {
    s32 i;

    for (i = 0; i < 70; i++) {
        if (blockOwners[i] == 0) {
            blockOwners[i] = owner;
            return blocks[i];
        }
    }
    FatalError("AllocBlock: Out of Blocks.\n");
    return 0;
}

/*
=====================
FreeBlocks

Frees the data blocks a proc owns.
=====================
*/
void FreeBlocks(s32 owner) {
    s32 i;

    for (i = 0; i < 70; i++) {
        if (blockOwners[i] == owner) {
            blockOwners[i] = 0;
        }
    }
}

/*
=====================
KillProc

Unlinks a proc and frees its blocks, and its objs if asked.
=====================
*/
s32 KillProc(proc_t *proc, s32 killObjs) {
    proc_t *prev;
    proc_t *next;

    prev = GetProcBefore(proc);
    if (prev == 0) {
        return 0;
    }
    next = proc->next;
    prev->next = next;
    numProcs--;
    proc->handler = 0;
    FreeBlocks(proc->id);
    if (killObjs != 0) {
        FreeProcObjs(proc->id);
    }
    return 1;
}

/*
=====================
CreatProc

Makes a proc with a handler and a class, links it at the end of the list, gives it a data block and
the start message (8).
=====================
*/
proc_t *CreatProc(procHandler_t handler, s32 cls) {
    proc_t *last;
    proc_t *task;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    last = GetLastProc();
    task = AllocProc();
    if (task == 0) {
        FatalError("CreatProc: Failed to alloc proc\n");
        return 0;
    }
    last->next = task;
    task->handler = handler;
    task->cls = cls;
    task->sleep = 0;
    task->event = PRC_EVENT_NULL;
    task->items[0] = PRC_EVENT_INIT;
    task->count = 1;
    task->next = 0;
    task->creatZero1 = 0;
    task->creatZero2 = 0;
    task->data = AllocBlock(task->id);
    return task;
}

/*
=====================
DoProcs

Runs each live proc's handler once a frame, unless it sleeps or waits, and acts on what the handler
returns. While the game is paused only the pause proc runs.
=====================
*/
void DoProcs(void) {
    struct procResult_s res;
    proc_t *task;

    task = &procst[0];
    while (task->next != 0) {
        task = task->next;
        if (task->handler == 0) {
            FatalError("DoProcs: Tried to execute a NULL\n");
            return;
        }
        if (task->waiting == 0) {
            if (task->sleep > 0) {
                if (gameMode != 6) {
                    task->sleep--;
                }
            } else {
                if (gameMode == 6) {
                    if (task->cls == 0xB000000) {
                        res = task->handler(task);
                    }
                } else {
                    res = task->handler(task);
                }
                switch (res.w[1]) {
                case 0:
                    KillProc(task, res.w[0]);
                    break;
                case 1:
                    task->sleep = res.w[0];
                    break;
                case 2:
                    task->event = res.w[0];
                    task->waiting = 1;
                    break;
                case 3:
                    task->event = res.w[0];
                    break;
                }
            }
        }
    }
}

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
            node->event = PRC_EVENT_NULL;
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
