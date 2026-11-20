#include "wof.h"

s32 func_8000A4A4(s32 arg0, s32 arg1) {
    proc_t *prev;
    s32 next;

    prev = (proc_t *)func_8000A158(arg0);
    if (prev == 0) {
        return 0;
    }
    next = ((proc_t *)arg0)->next;
    prev->next = next;
    D_800BEE50--;
    ((proc_t *)arg0)->unk_00 = 0;
    func_8000A408(((proc_t *)arg0)->unk_04);
    if (arg1 != 0) {
        func_8000B2D4(((proc_t *)arg0)->unk_04);
    }
    return 1;
}
