#include "wof.h"

struct n64dk_r12 func_80033A28(proc_t *proc) {
    struct n64dk_r12 result;
    s32 event;
    s32 sp24;

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = func_8000ACE8(proc)) != 0) {
        switch (event) {
        case 8:
            func_80002CE0(10);
            D_800B96A8 = 2;
            proc->unk_30->data80033A28.unk_04 = 0;
            proc->unk_30->data80033A28.unk_08 = 0;
            break;
        }
    }
    if (proc->unk_30->data80033A28.unk_04 > 0) {
        switch (proc->unk_30->data80033A28.unk_04) {
        case 1:
            sp24 = func_80002CE0(8);
            break;
        case 2:
            sp24 = func_80002CE0(9);
            break;
        case 3:
            sp24 = func_80002CE0(10);
            break;
        default:
            sp24 = func_80002CE0(guRandom() % 3 + 16);
        }
        if (D_800B96A8 == proc->unk_30->data80033A28.unk_04) {
            D_800B96A8 = 0;
            proc->unk_30->data80033A28.unk_04 = 0;
        }
    }
    if (proc->unk_30->data80033A28.unk_04 < D_800B96A8) {
        proc->unk_30->data80033A28.unk_04++;
        result.w[0] = 10 / D_800B96B4;
    }
    return result;
}
