#include "wof.h"

void func_80028C4C(proc_t *proc) {
    proc->data->cursor.index = 2;
    if (D_800B9CF8 != 0) {
        proc->data->cursor.index = 0;
        return;
    }
    if (D_800B9CFC != 0) {
        proc->data->cursor.index = 1;
    }
}
