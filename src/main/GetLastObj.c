#include "wof.h"

obj_t *GetLastObj(void) {
    obj_t *next;
    obj_t *node;

    node = &objst[0];
    next = node->next;
    while (next != 0) {
        node = next;
        next = node->next;
    }
    return node;
}
