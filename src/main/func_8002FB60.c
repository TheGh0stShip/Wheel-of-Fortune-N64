#include "wof.h"


struct procResult_s func_8002FB60(proc_t *proc) {
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
    if ((sp2C - proc->unk_30->timer.start) >= 5) {
        ProcPostEvent(48);
        sp10.w[1] = 0;
    }
    return sp10;
}
