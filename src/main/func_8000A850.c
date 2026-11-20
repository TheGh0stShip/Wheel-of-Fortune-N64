#include "wof.h"

void func_8000A850(s32 arg0) {
    s32 pad0[4];
    proc_t *node;

    if (arg0 >= 53) {
        func_80009F38("ProcPostEvent: bogus event\n");
        return;
    }
    node = &D_800B82A0[0];
    while (node->next != 0) {
        node = node->next;
        if (node->unk_10 == arg0 || node->unk_10 == -1) {
            node->unk_10 = 0;
            node->unk_14 = 0;
            node->unk_0C = 0;
            if (node->count < 5) {
                node->items[node->count] = arg0;
                node->count++;
            } else {
                func_80009F38("ProcPostEvent: Message Que overrun.\n");
            }
        }
    }
}
