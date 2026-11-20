#include "wof.h"

struct procResult_s func_80033688(proc_t *proc) {
    struct procResult_s sp10;
    proc_t *sp20;
    s32 unused;  /* NOTE: unused in the original */
    s32 sp28;

    sp10.w[1] = 1;
    sp10.w[0] = 0;
    for (;;) {
        sp28 = ProcGetMessage(proc);
        if (sp28 == 0) {
            break;
        }
        switch (sp28) {
        case 8:
            D_800BEE48 = (s32)(osGetTime() / osClockRate);
        }
    }
    D_800BCA1C = 0;
    if (gameMode == 2) {
        if (D_800BED88 > 0) {
            D_800BEE48 = (s32)(osGetTime() / osClockRate);
            D_800BED88 = 0;
        } else {
            if (((osGetTime() / osClockRate) - D_800BEE48) > 30) {
                func_800335D0();
                return sp10;
            }
        }
    } else {
        if (gameMode == 8) {
            if (((buttonsPressed & 0xB000) & 0xFFFF) != 0) {
                sp20 = FindProc(0x6060000, -1);
                if (sp20 != 0) {
                    ProcPostMessage(sp20, 46, 1);
                }
            }
            return sp10;
        }
    }
    if (((buttonsPressed & 0x1000) & 0xFFFF) != 0) {
        if (gameMode != 6) {
            func_800335D0();
        } else {
            FreeObjClass(0x5020000, -1);
            gameMode = D_800BED98;
            ResumeSounds();
            D_800BCA1C = ((s32)(osGetTime() / osClockRate)) - D_800BA2C0;
            D_800BEE48 = (s32)(osGetTime() / osClockRate);
        }
    }
    return sp10;
}
