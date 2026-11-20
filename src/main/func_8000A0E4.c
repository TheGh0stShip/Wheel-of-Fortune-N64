#include "wof.h"

s32 func_8000A0E4(void) {
    proc_t *next;
    proc_t *node;

    node = &D_800B82A0[0];
    next = node->next;
    while (next != 0) {
        node = next;
        next = node->next;
    }
    return (s32)node;
}
