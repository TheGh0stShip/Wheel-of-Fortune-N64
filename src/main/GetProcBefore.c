#include "wof.h"

proc_t *GetProcBefore(proc_t *proc) {
    proc_t *cur;
    proc_t *prev;

    prev = &procst[0];
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
