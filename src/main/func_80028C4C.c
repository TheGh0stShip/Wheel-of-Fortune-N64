#include "wof.h"

void func_80028C4C(proc_t *proc) {
    ((cursor_t *)proc->unk_30)->index = 2;
    if (D_800B9CF8 != 0) {
        ((cursor_t *)proc->unk_30)->index = 0;
        return;
    }
    if (D_800B9CFC != 0) {
        ((cursor_t *)proc->unk_30)->index = 1;
    }
}
