#include "wof.h"

proc_t *func_8000A158(proc_t *proc) {
    proc_t *cur;
    proc_t *prev;

    prev = &D_800B82A0[0];
    cur = prev->next;
    while (cur != 0) {
        if (cur == proc) {
            return prev;
        }
        prev = cur;
        cur = prev->next;
    }
    func_80009F38("GetProcBefore: Could not find proc\n");
    return 0;
}
