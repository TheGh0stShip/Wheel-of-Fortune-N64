#include "wof.h"

void func_8000ADEC(s32 arg0) {
    s32 sp10;
    s32 pad0;
    s32 pad1[2];
    proc_t *node;

    node = &D_800B82A0[0];
    while (node->next != 0) {
        node = node->next;
        if ((s32)node != arg0) {
            func_8000A4A4((s32)node, sp10);
        }
    }
}
