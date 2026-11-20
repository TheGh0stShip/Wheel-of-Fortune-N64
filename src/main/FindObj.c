#include "wof.h"

obj_t *FindObj(s32 cls, s32 mask) {
    obj_t *node;

    node = &objst[0];
    while (node->next != 0) {
        node = node->next;
        if ((node->unk_08 & mask) == cls) {
            return node;
        }
    }
    return 0;
}
