#include "wof.h"

obj_t *func_8000B5DC(s32 arg0, s32 arg1) {
    obj_t *node;

    node = &D_800B40C8[0];
    while (node->next != 0) {
        node = node->next;
        if ((node->unk_08 & arg1) == arg0) {
            return node;
        }
    }
    return 0;
}
