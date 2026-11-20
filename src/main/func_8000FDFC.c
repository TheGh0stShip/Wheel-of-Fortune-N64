#include "wof.h"

struct n64dk_r12 func_8000FDFC(proc_t *proc) {
    struct n64dk_r12 ret;
    s32 sp20;
    s32 event;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    sp20 = proc->unk_30->data8000FDFC.unk_00;
    while ((event = func_8000ACE8(proc)) != 0) {
        switch (event) {
        case 8:
            func_80016098();
            func_80032B10();
            func_80032AD4(1);
            proc->unk_30->data8000FDFC.unk_04 = 0;
            D_800B96A8++;
            func_8000AAB0(proc, 41, 0);
            return func_8000FC3C(proc);
        case 41:
            D_800B96A8 += D_800B9990[D_800FB808].unk_000 / 5000;
            return func_8000FC3C(proc);
        case 34:
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        }
    }
    return func_8000FC3C(proc);
}
