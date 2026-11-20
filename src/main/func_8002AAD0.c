#include "wof.h"


void func_8002AAD0(proc_t *proc, s32 arg1, s32 arg2) {
    D_800BED88++;
    if (arg2 != 0) {
        func_80002CE0(43);
    }
    if (arg1 != 0) {
        proc->unk_30->cursor.index++;
        if (proc->unk_30->cursor.index == 13) {
            proc->unk_30->cursor.index = 0;
        }
        if (proc->unk_30->cursor.index >= 26) {
            proc->unk_30->cursor.index = 13;
        }
        D_8005A998[proc->unk_30->cursor.index].unk_1C = D_8005A998[proc->unk_30->cursor.index].unk_14;
    } else {
        if (proc->unk_30->cursor.index != 3) {
            proc->unk_30->cursor.index++;
            if (proc->unk_30->cursor.index >= 3) {
                proc->unk_30->cursor.index = 0;
            }
        }
        D_8005A828[proc->unk_30->cursor.index].unk_1C = D_8005A828[proc->unk_30->cursor.index].unk_14;
    }
    D_800B61B5 = proc->unk_30->cursor.index + 65;
    proc->unk_30->cursor.unk_0C = 15;
}
