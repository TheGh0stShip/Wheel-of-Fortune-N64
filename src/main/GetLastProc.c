#include "wof.h"

proc_t *GetLastProc(void) {
    proc_t *next;
    proc_t *node;

    node = &procst[0];
    next = node->next;
    while (next != 0) {
        node = next;
        next = node->next;
    }
    return node;
}
