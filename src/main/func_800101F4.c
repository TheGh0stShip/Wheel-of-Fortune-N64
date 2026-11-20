#include "wof.h"

struct n64dk_r12 func_800101F4(proc_t *proc) {
    struct n64dk_r12 result;
    obj_t *obj;
    s32 event;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    obj = proc->unk_30->data800101F4.unk_00;
    for (;;) {
        event = func_8000ACE8(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            proc->unk_30->data800101F4.unk_08 = 0;
            obj->unk_48 = &D_011358C0;
            break;
        case 2:
            obj->unk_48 = &D_01135878;
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    proc->unk_30->data800101F4.unk_08 = proc->unk_30->data800101F4.unk_08 + D_800B96B4;
    if (proc->unk_30->data800101F4.unk_08 >= 6) {
        proc->unk_30->data800101F4.unk_08 = 0;
        if (obj->unk_48 == &D_011358C0) {
            obj->unk_48 = &D_01135908;
        } else {
            obj->unk_48 = &D_011358C0;
        }
    }
    result.w[1] = 3;
    result.w[0] = -1;
    return result;
}
