#include "wof.h"


struct n64dk_r12 func_8002F7CC(proc_t *proc) {
    struct n64dk_r12 sp10;
    OSTime time; /* NOTE: unused in the original. Eight bytes nothing touches; guess: an OSTime */
    s32 sp28;
    s32 sp2C;

    sp10.w[1] = 1;
    sp10.w[0] = 0;
    for (;;) {
        sp28 = func_8000ACE8(proc);
        if (sp28 == 0) {
            break;
        }
        switch (sp28) {
        case 8:
            proc->unk_30->timer.start = (s32)(osGetTime() / osClockRate);
            break;
        }
    }
    sp2C = (s32)(osGetTime() / osClockRate);
    if (((sp2C - proc->unk_30->timer.start) >= 30) || (((D_800B96B0 & 0x1000) & 0xFFFF) != 0)) {
        func_8000ABB8(34, 0, 0, 1);
        sp10.w[1] = 0;
    }
    return sp10;
}
