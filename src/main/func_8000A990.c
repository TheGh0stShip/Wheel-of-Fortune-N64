#include "wof.h"

s32 func_8000A990(s32 arg0, s32 arg1) {
    proc_t *node;

    node = &D_800B82A0[0];
    while (node->next != 0) {
        node = node->next;
        if ((node->unk_08 & arg1) == arg0) {
            return (s32)node;
        }
    }
    return 0;
}
