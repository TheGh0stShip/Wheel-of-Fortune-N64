#include "wof.h"

s32 func_8000A158(s32 arg0) {
    proc_t *cur;
    proc_t *prev;

    prev = &D_800B82A0[0];
    cur = prev->next;
    while (cur != 0) {
        if ((s32)cur == arg0) {
            return (s32)prev;
        }
        prev = cur;
        cur = prev->next;
    }
    func_80009F38("GetProcBefore: Could not find proc\n");
    return 0;
}
