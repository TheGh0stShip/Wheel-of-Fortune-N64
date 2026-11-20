#include "wof.h"

void ProcPostEvent(s32 event) {
    struct procResult_s unused;  /* NOTE: unused in the original; DoProcs uses its own */
    proc_t *node;

    if (event >= 53) {
        func_80009F38("ProcPostEvent: bogus event\n");
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
                func_80009F38("ProcPostEvent: Message Que overrun.\n");
            }
        }
    }
}
