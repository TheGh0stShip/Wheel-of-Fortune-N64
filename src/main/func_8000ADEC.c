#include "wof.h"

void func_8000ADEC(s32 arg0) {
    struct n64dk_r12 res;
    proc_t *node;

    node = &D_800B82A0[0];
    while (node->next != 0) {
        node = node->next;
        if ((s32)node != arg0) {
            func_8000A4A4((s32)node, res.w[0]);  // BUG: res is never set
        }
    }
}
