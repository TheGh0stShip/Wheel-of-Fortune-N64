#include "wof.h"


struct procResult_s func_80021744(proc_t *proc) {
    s32 event;
    struct procResult_s result;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            if (proc->data->data80021744.unk_24 > 0) {
                D_800B8294 = proc->data->data80021744.unk_24;
            }
            minRetraces = 8;
            break;
        case 34:
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
    }
    func_800213CC(proc);
    if (D_800B40C4 != 0) {
        SetGameView(3, 0);
        D_800B96A4 = 0;
        PopMemStack(1);
        minRetraces = 0;
        result.w[1] = 0;
        result.w[0] = 1;
        func_800325D0(1, proc->data->data80021744.unk_10);
        if (proc->data->data80021744.unk_20 != 0) {
            ProcPostEvent(proc->data->data80021744.unk_20);
        }
    }
    return result;
}
