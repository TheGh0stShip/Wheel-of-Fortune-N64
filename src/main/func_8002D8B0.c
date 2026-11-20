#include "wof.h"


void func_8002D8B0(s32 arg0) {
    if (D_800B966A[((proc_t *)arg0)->unk_30->cursor.index] == 32) {
        func_8002AAD0(arg0, 1, 0);
    }
    D_800B61B5 = ((proc_t *)arg0)->unk_30->cursor.index + 65;
}
