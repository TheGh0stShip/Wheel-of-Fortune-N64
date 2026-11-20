#include "wof.h"


struct procResult_s func_8002F338(proc_t *proc) {
    struct procResult_s sp10;
    OSTime time; /* NOTE: unused in the original. Eight bytes nothing touches; guess: an OSTime */
    s32 sp28;
    s32 sp2C;
    s32 sp30;

    sp10.w[1] = 1;
    sp10.w[0] = 0;
    for (;;) {
        sp28 = ProcGetMessage(proc);
        if (sp28 == 0) {
            break;
        }
        switch (sp28) {
        case 8:
            D_800B81DC = 0;
            sp30 = 0;
            for (;;) {
                if (sp30 >= 3) {
                    break;
                }
                if (D_800B9990[sp30].unk_014 == 4) {
                    D_800B81DC = D_800B81DC + 240;
                } else {
                    D_800B81DC = D_800B81DC + 300;
                }
                sp30++;
            }
        case 43:
            proc->data->timer.start = (s32)(osGetTime() / osClockRate);
            break;
        }
    }
    D_800B81DC = D_800B81DC + D_800BCA1C;
    sp2C = (s32)(osGetTime() / osClockRate);
    if ((sp2C - proc->data->timer.start) >= D_800B81DC) {
        if (FindProc(0x5010000, -1) != 0) {
            return sp10;
        }
        if (FindProc(0x5020000, -1) != 0) {
            return sp10;
        }
        if (FindProc(0x2000100, 0xFF00FF00) != 0) {
            return sp10;
        }
        if (FindProc(0x2000200, 0xFF00FF00) != 0) {
            return sp10;
        }
        if (FindProc(0x2000300, 0xFF00FF00) != 0) {
            return sp10;
        }
        if (FindProc(0x2000500, 0xFF00FF00) != 0) {
            return sp10;
        }
        if (FindProc(0x7050000, 0xFF00FF00) != 0) {
            return sp10;
        }
        if (((f64)CheckPercentDone()) < 0.6) {
            PlaySound(3);
            CreatProc(func_8002EFC0, 0x7020000);
            ProcPostMessageClass(30, 0, 0, 0);
        }
        D_800B9CF0 = 1;
        sp10.w[1] = 0;
        sp10.w[0] = 0;
        return sp10;
    }
    return sp10;
}
