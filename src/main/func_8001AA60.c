#include "wof.h"

void func_8001AA60(proc_t *proc) {
    proc_t *task;
    s32 sp14;
    f32 score;
    f32 sp1C;
    f32 sp20;

    sp14 = 0;
    sp20 = CheckPercentDone();
    task = FindProc(0x5000000, -1);
    if (D_800B9D00 != 0) {
        if (D_800B96A0 != 0) {
            if (sp20 > 0.6) {
                D_800B61B5 = 50;
                ProcPostMessage(proc, 14, 0);
                ProcPostMessage(task, 27, 0);
                return;
            }
        }
        if (sp20 > 0.7 || D_800B9CF8 == 0) {
            D_800B61B5 = 50;
            ProcPostMessage(proc, 14, 0);
            ProcPostMessage(task, 27, 0);
            return;
        }
    }
    if (D_800B9CF8 != 0) {
        sp1C = (f32)Random(100);
        sp1C = sp1C / 100.0f;
        score = (f32)StrLen(D_800B61C0);
        score = score / 21.0f;
        score = score * 0.15;
        score = score + sp1C;
        switch (func_800084E8()) {
        case 4:
            if (score < proc->unk_30->playerProc.unk_0C || D_800B9990[D_800FB808].unk_000 < 250) {
                D_800B61B5 = 48;
                ProcPostMessage(proc, 12, 0);
            } else {
                D_800B61B5 = 49;
                ProcPostMessage(proc, 13, 0);
            }
            break;
        case 3:
            D_800B61B5 = 48;
            ProcPostMessage(proc, 12, 0);
            break;
        case 2:
            D_800B61B5 = 49;
            ProcPostMessage(proc, 13, 0);
            break;
        }
    } else if (D_800B9CFC != 0) {
        if (StrLen(D_800B6AE0) != 0) {
            D_800B61B5 = 49;
            ProcPostMessage(proc, 13, 0);
        } else {
            D_800B61B5 = 48;
            ProcPostMessage(proc, 12, 0);
        }
    }
    ProcPostMessage(task, 27, 0);
}
