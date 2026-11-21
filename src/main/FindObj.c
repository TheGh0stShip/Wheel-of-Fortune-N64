#include "wof.h"

/*
=====================
FindObj

The first obj whose class under a mask is a value.
=====================
*/
obj_t *FindObj(s32 cls, s32 mask) {
    obj_t *node;

    node = &objst[0];
    while (node->next != 0) {
        node = node->next;
        if ((node->cls & mask) == cls) {
            return node;
        }
    }
    return 0;
}
