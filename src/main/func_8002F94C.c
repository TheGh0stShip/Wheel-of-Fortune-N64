#include "wof.h"


struct procResult_s func_8002F94C(proc_t *proc) {
    struct procResult_s sp10;
    OSTime time; /* NOTE: unused in the original. Eight bytes nothing touches; guess: an OSTime */
    s32 sp28;
    s32 sp2C;

    sp10.w[1] = 1;
    sp10.w[0] = 0;
    for (;;) {
        sp28 = ProcGetMessage(proc);
        if (sp28 == 0) {
            break;
        }
        switch (sp28) {
        case 8:
            proc->unk_30->timer.start = (s32)(osGetTime() / osClockRate);
            break;
        }
    }
    proc->unk_30->timer.start = proc->unk_30->timer.start + D_800BCA1C;
    sp2C = (s32)(osGetTime() / osClockRate);
    if (D_800BCD54 == 4) {
        D_800B40C0 = 20 - (sp2C - proc->unk_30->timer.start);
        if ((sp2C - proc->unk_30->timer.start) >= 20) {
            D_800B40C0 = 0;
            ProcPostMessageClass(33, 0, 0, 0);
            sp10.w[1] = 0;
        }
    } else {
        if ((sp2C - proc->unk_30->timer.start) >= 8) {
            ProcPostMessageClass(33, 0, 0, 0);
            ProcPostEvent(33);
            sp10.w[1] = 0;
        }
    }
    return sp10;
}
