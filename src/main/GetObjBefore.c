#include "wof.h"

obj_t *GetObjBefore(obj_t *obj) {
    obj_t *next;
    obj_t *node;

    node = &objst[0];
    next = node->next;
    while (next != 0) {
        if (next == obj) {
            return node;
        }
        node = next;
        next = node->next;
    }
    func_80009F38("GetObjBefore: Could not find obj\n");
    return 0;
}
