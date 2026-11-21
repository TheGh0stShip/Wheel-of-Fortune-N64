// ProcPostEvent.c -- gives an event to every proc that waits for it, or for any, as a message, and
// wakes it

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
