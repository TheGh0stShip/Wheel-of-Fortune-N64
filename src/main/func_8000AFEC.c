#include "wof.h"

s32 func_8000AFEC(void) {
    obj_t *next;
    obj_t *node;

    node = &D_800B40C8[0];
    next = node->next;
    while (next != 0) {
        node = next;
        next = node->next;
    }
    return (s32)node;
}
