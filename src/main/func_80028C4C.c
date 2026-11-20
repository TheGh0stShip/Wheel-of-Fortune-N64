#include "wof.h"

void func_80028C4C(proc_t *proc) {
    proc->unk_30->cursor.index = 2;
    if (D_800B9CF8 != 0) {
        proc->unk_30->cursor.index = 0;
        return;
    }
    if (D_800B9CFC != 0) {
        proc->unk_30->cursor.index = 1;
    }
}
