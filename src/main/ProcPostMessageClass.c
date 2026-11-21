// ProcPostMessageClass.c -- procPostMessage to every proc of a class

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
