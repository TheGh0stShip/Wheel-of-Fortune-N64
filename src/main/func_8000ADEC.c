#include "wof.h"

void func_8000ADEC(proc_t *proc) {
    struct n64dk_r12 res;
    proc_t *node;

    node = &D_800B82A0[0];
    while (node->next != 0) {
        node = node->next;
        if (node != proc) {
            func_8000A4A4(node, res.w[0]);  // BUG: res is never set
        }
    }
}
