#include "wof.h"

struct procResult_s func_80021548(proc_t *proc) {
    s32 event;
    struct procResult_s ret;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    ret.w[1] = 1;
    ret.w[0] = 0;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            if (proc->unk_30->data80021548.unk_24 > 0) {
                D_800B8294 = proc->unk_30->data80021548.unk_24;
            }
            minRetraces = 4;
            break;
        case 34:
            ret.w[1] = 0;
            ret.w[0] = 1;
            return ret;
        }
    }
    func_800212C0(proc);
    if (D_800B40C4 != 0) {
        PopMemStack(1);
        minRetraces = 0;
        ret.w[1] = 0;
        ret.w[0] = 1;
        if (D_800B40C4 == 2) {
            func_800A4E58(0);
            func_800219B8(D_800BCA28, proc->unk_30->data80021548.unk_20, proc->unk_30->data80021548.unk_00->x, proc->unk_30->data80021548.unk_00->y);
        } else if (proc->unk_30->data80021548.unk_20 != 0) {
            ProcPostEvent(proc->unk_30->data80021548.unk_20);
        }
    }
    return ret;
}
