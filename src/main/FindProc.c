#include "wof.h"

proc_t *FindProc(s32 cls, s32 mask) {
    proc_t *node;

    node = &procst[0];
    while (node->next != 0) {
        node = node->next;
        if ((node->unk_08 & mask) == cls) {
            return node;
        }
    }
    return 0;
}
