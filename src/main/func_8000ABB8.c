#include "wof.h"


void func_8000ABB8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    proc_t *node;

    node = func_8000A990(arg1, arg2);
    while (node != 0) {
        if (arg0 >= 53) {
            func_80009F38("ProcPostMessageClass: bogus message\n");
            return;
        }
        if (node->count < 5) {
            node->items[node->count] = arg0;
            node->count++;
        } else {
            func_80009F38("ProcPostMessageClass: Message Que overrun.\n");
        }
        if (arg3 != 0) {
            node->unk_14 = 0;
            node->unk_0C = 0;
        }
        node = func_8000AA24(node, arg1, arg2);
    }
}
