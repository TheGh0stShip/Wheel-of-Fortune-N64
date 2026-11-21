#include "wof.h"


struct procResult_s CreditsProc(proc_t *proc) {
    s32 event;
    s32 i;
    struct procResult_s ret;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    ret.w[1] = 1;
    ret.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            i = 0;
            for (;;) {
                if (i >= 22) {
                    break;
                }
                categoryImages[i].unk_20 = 0;
                categoryImages[i].unk_24 = 0;
                i++;
            }
            ResetMotors();
            MakeScreenObj(0, 0, func_80028064, 0x5050000);
            proc->data->data8002B318.step = 0;
            gameMode = 8;
            FreeObjClass(0x5050100, -1);
            KillProcClass(0xA000400, -1, 1);
            FreeObjClass(0xA030000, -1);
            PlaySound(21);
            break;
        case 46:
            StopAllSounds();
            ret.w[1] = 1;
            ret.w[0] = 2;
            FreeObjClass(0x1000000, 0xFF000000);
            FreeObjClass(0xA000000, 0xFF000000);
            FreeObjClass(0x4000000, 0xFF000000);
            ProcPostMessage(proc, 35, 0);
            return ret;
        case 35:
            KillOtherProcs(proc);
            InitObjs();
            StopMovie();
            RestartOpening();
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        }
    }
    if (proc->data->data8002B318.step >= 22) {
        ProcPostMessage(proc, 46, 0);
        return ret;
    }
    ResetBoard();
    LoadPuzzle(0, creditsText[proc->data->data8002B318.step]);
    if (creditsTitles[proc->data->data8002B318.step] != 0) {
        StrCopy(category, creditsTitles[proc->data->data8002B318.step]);
        InitCategory();
    }
    RevealPuzzle();
    proc->data->data8002B318.step++;
    ret.w[0] = 65 / frameRetraces;
    return ret;
}
