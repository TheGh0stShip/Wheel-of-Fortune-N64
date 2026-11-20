#include "wof.h"


void func_8002A8C8(proc_t *proc, s32 arg1) {
    D_800BED88++;
    PlaySound(43);
    if (arg1 != 0) {
        proc->data->cursor.index--;
        if (proc->data->cursor.index == 12) {
            proc->data->cursor.index = 25;
        }
        if (proc->data->cursor.index < 0) {
            proc->data->cursor.index = 12;
        }
        D_8005A998[proc->data->cursor.index].unk_1C = D_8005A998[proc->data->cursor.index].unk_14;
    } else {
        if (proc->data->cursor.index != 3) {
            proc->data->cursor.index--;
        }
        if (proc->data->cursor.index < 0) {
            proc->data->cursor.index = 2;
        }
        D_8005A828[proc->data->cursor.index].unk_1C = D_8005A828[proc->data->cursor.index].unk_14;
    }
    D_800B61B5 = proc->data->cursor.index + 65;
    proc->data->cursor.unk_0C = 15;
}
