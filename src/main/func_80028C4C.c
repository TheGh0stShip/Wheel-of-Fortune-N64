#include "wof.h"

void func_80028C4C(proc_t *proc) {
    proc->data->cursor.index = 2;
    if (canSpin != 0) {
        proc->data->cursor.index = 0;
        return;
    }
    if (canBuyVowel != 0) {
        proc->data->cursor.index = 1;
    }
}
