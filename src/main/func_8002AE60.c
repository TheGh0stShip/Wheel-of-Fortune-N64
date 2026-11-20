#include "wof.h"


void func_8002AE60(proc_t *proc) {
    s32 i;

    D_800BED88++;
    if (proc->data->cursor.index >= 13) {
        return;
    }
    i = 13;
    while (i < 26) {
        if (D_800B966A[i] != 32) {
            break;
        }
        i++;
    }
    if (i == 26) {
        return;
    }
    PlaySound(43);
    proc->data->cursor.index += 13;
    D_8005A998[proc->data->cursor.index].unk_1C = D_8005A998[proc->data->cursor.index].unk_14;
    D_800B61B5 = proc->data->cursor.index + 65;
    proc->data->cursor.unk_0C = 15;
}
