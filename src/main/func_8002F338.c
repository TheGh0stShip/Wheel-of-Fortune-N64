#include "wof.h"


struct n64dk_r12 func_8002F338(proc_t *proc) {
    struct n64dk_r12 sp10;
    OSTime time; /* NOTE: unused in the original. Eight bytes nothing touches; guess: an OSTime */
    s32 sp28;
    s32 sp2C;
    s32 sp30;

    sp10.w[1] = 1;
    sp10.w[0] = 0;
    for (;;) {
        sp28 = func_8000ACE8(proc);
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
            proc->unk_30->timer.start = (s32)(osGetTime() / D_80084218);
            break;
        }
    }
    D_800B81DC = D_800B81DC + D_800BCA1C;
    sp2C = (s32)(osGetTime() / D_80084218);
    if ((sp2C - proc->unk_30->timer.start) >= D_800B81DC) {
        if (func_8000A990(0x5010000, -1) != 0) {
            return sp10;
        }
        if (func_8000A990(0x5020000, -1) != 0) {
            return sp10;
        }
        if (func_8000A990(0x2000100, 0xFF00FF00) != 0) {
            return sp10;
        }
        if (func_8000A990(0x2000200, 0xFF00FF00) != 0) {
            return sp10;
        }
        if (func_8000A990(0x2000300, 0xFF00FF00) != 0) {
            return sp10;
        }
        if (func_8000A990(0x2000500, 0xFF00FF00) != 0) {
            return sp10;
        }
        if (func_8000A990(0x7050000, 0xFF00FF00) != 0) {
            return sp10;
        }
        if (((f64)func_80008628()) < 0.6) {
            func_80002CE0(3);
            func_8000A56C(func_8002EFC0, 0x7020000);
            func_8000ABB8(30, 0, 0, 0);
        }
        D_800B9CF0 = 1;
        sp10.w[1] = 0;
        sp10.w[0] = 0;
        return sp10;
    }
    return sp10;
}
