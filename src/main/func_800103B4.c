#include "wof.h"

struct n64dk_r12 func_800103B4(proc_t *proc) {
    struct n64dk_r12 sp10;
    obj_t *sprite;
    s32 event;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    sprite = proc->unk_30->data800103B4.unk_00;
    while ((event = func_8000ACE8(proc)) != 0) {
        switch (event) {
        case 8:
            proc->unk_30->data800103B4.unk_08 = 0;
            sprite->unk_48 = D_01136108;
            break;
        case 2:
            sprite->unk_48 = D_01135FF8;
            sp10.w[1] = 0;
            sp10.w[0] = 0;
            return sp10;
        }
    }
    proc->unk_30->data800103B4.unk_08 = proc->unk_30->data800103B4.unk_08 + D_800B96B4;
    if (proc->unk_30->data800103B4.unk_08 >= 6) {
        proc->unk_30->data800103B4.unk_08 = 0;
        if (sprite->unk_48 == D_01136080) {
            sprite->unk_48 = D_01136108;
        } else {
            sprite->unk_48 = D_01136080;
        }
    }
    sp10.w[1] = 3;
    sp10.w[0] = -1;
    return sp10;
}
