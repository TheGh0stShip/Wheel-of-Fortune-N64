#include "wof.h"

struct n64dk_r12 func_80016734(proc_t *proc) {
    s32 event;
    struct n64dk_r12 result;
    obj_t *sp28;

    sp28 = proc->unk_30->data80016734.unk_00;
    result.w[1] = 1;
    result.w[0] = 0;
    for (;;) {
        event = func_8000ACE8(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            D_800BA5D8 = &proc->unk_30->data80016734.unk_08[proc->unk_30->data80016734.unk_0C];
            return result;
        }
    }
    proc->unk_30->data80016734.unk_0C += D_800B96B4;
    if (proc->unk_30->data80016734.unk_0C >= proc->unk_30->data80016734.unk_10) {
        D_800BA5D8 = proc->unk_30->data80016734.unk_08 - 1 + proc->unk_30->data80016734.unk_10;
        func_8000A850(45);
        result.w[1] = 0;
        result.w[0] = 0;
        return result;
    }
    D_800BA5D8 = &proc->unk_30->data80016734.unk_08[proc->unk_30->data80016734.unk_0C];
    return result;
}
