#include "wof.h"


void func_8002D8B0(proc_t *proc) {
    if (D_800B966A[proc->unk_30->cursor.index] == 32) {
        func_8002AAD0(proc, 1, 0);
    }
    D_800B61B5 = proc->unk_30->cursor.index + 65;
}
