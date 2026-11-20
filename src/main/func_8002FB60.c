#include "wof.h"


struct n64dk_r12 func_8002FB60(proc_t *proc) {
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
            proc->unk_30->timer.start = (s32)(osGetTime() / D_80084218);
            break;
        }
    }
    proc->unk_30->timer.start = proc->unk_30->timer.start + D_800BCA1C;
    sp2C = (s32)(osGetTime() / D_80084218);
    if ((sp2C - proc->unk_30->timer.start) >= 5) {
        func_8000A850(48);
        sp10.w[1] = 0;
    }
    return sp10;
}
