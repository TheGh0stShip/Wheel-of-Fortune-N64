#include "wof.h"


void func_8002ACE8(proc_t *proc) {
    s32 i;

    D_800BED88++;
    if (proc->unk_30->cursor.index < 13) {
        return;
    }
    i = 0;
    for (;;) {
        if (i >= 13) {
            break;
        }
        if (D_800B966A[i] != 32) {
            break;
        }
        i++;
    }
    if (i == 13) {
        return;
    }
    PlaySound(43);
    proc->unk_30->cursor.index = proc->unk_30->cursor.index - 13;
    D_8005A998[proc->unk_30->cursor.index].unk_1C = D_8005A998[proc->unk_30->cursor.index].unk_14;
    D_800B61B5 = proc->unk_30->cursor.index + 65;
    proc->unk_30->cursor.unk_0C = 15;
}
