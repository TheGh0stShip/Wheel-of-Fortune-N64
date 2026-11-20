#include "wof.h"

s32 func_8000B060(s32 arg0) {
    s32 next;
    obj_t *node;

    node = &D_800B40C8[0];
    next = node->next;
    while (next != 0) {
        if (next == arg0) {
            return (s32)node;
        }
        node = (obj_t *)next;
        next = node->next;
    }
    func_80009F38("GetObjBefore: Could not find obj\n");
    return 0;
}
