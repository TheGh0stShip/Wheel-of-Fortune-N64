#include "wof.h"

struct procResult_s func_8002C094(proc_t *proc) {
    s32 event;
    s32 i;
    struct procResult_s ret;
    proc_t *task;

    ret.w[1] = 1;
    ret.w[0] = 0;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            D_800BEE20 = -1;
            for (i = 0; i < 5; i++) {
                D_800B61B0[i] = 0;
            }
            D_800BEE28 = 0;
            D_800BEE4C = 0;
            func_8002B054();
            func_80029440();
            ret.w[1] = 1;
            ret.w[0] = 60 / frameRetraces;
            ProcPostMessage(proc, 11, 0);
            return ret;
        case 11:
            if (lightDir < 0) {
                func_80021B04(9, 44);
            } else {
                func_800219B8(9, 44, 180, 20);
            }
            ret.w[1] = 2;
            ret.w[0] = 44;
            return ret;
        case 44:
            for (i = 0; D_8005C394[i] != 0; i++) {
                uncalled[D_8005C394[i] - 65] = 32;
                ShowLetter(D_8005C394[i]);
            }
            task = CreatProc(LightTextProc, 0x1000000);
            task->data->data80010D3C.row = 0;
            task->data->data80010D3C.col = 0;
            task->data->data80010D3C.text = D_8005C394;
            ret.w[1] = 2;
            ret.w[0] = 6;
            return ret;
        case 6:
            if (D_8005BE00[9].unk_20 != 0) {
                if (CheckSolved(0) == 1) {
                    ProcPostEvent(10);
                    CreatProc(func_8002BE84, 0x6000000);
                    ret.w[1] = 0;
                    ret.w[0] = 1;
                    return ret;
                }
                D_800BEE20 = PlaySound(22);
                StartSolveTimer();
                StartSolvePuzzle();
                task = CreatProc(func_8002BA44, 0x5050200);
                func_80027218(task, 0, func_80028554, 0x5050200);
                ret.w[1] = 2;
                ret.w[0] = 10;
                return ret;
            }
            if (lightDir < 0) {
                func_80021B04(10, 0);
            } else {
                func_800219B8(10, 0, 180, 20);
            }
            StartLetterPick();
            ret.w[1] = 2;
            ret.w[0] = 5;
            return ret;
        case 5:
            if (IsVowel(curLetter) != 0) {
                if (D_8005BE00[9].unk_20 != 0) {
                    PlaySound(1);
                    StartLetterPick();
                    ret.w[1] = 2;
                    ret.w[0] = 5;
                    return ret;
                } else {
                    D_800BEE4C++;
                    i = 9;
                }
            } else {
                if (D_800BEE28 >= 3) {
                    PlaySound(1);
                    StartLetterPick();
                    ret.w[1] = 2;
                    ret.w[0] = 5;
                    return ret;
                }
                D_800BEE28++;
                i = 6;
            }
            while (i < 10 && D_8005BE00[i].unk_20 != 0) {
                i++;
            }
            uncalled[curLetter - 65] = 32;
            D_8005BE00[i].unk_20 = D_8005BCC8[curLetter - 65].unk_00;
            D_8005BE00[i].width = D_8005BCC8[curLetter - 65].width;
            D_8005BE00[i].height = D_8005BCC8[curLetter - 65].height;
            ShowLetter(curLetter);
            D_800B61AA[i] = curLetter;
            if (StrLen(D_800B61B0) == 4) {
                task = CreatProc(LightTextProc, 0x1000000);
                task->data->data80010D3C.row = 0;
                task->data->data80010D3C.col = 0;
                task->data->data80010D3C.text = D_800B61B0;
                ret.w[1] = 2;
                ret.w[0] = 6;
            } else {
                StartLetterPick();
                ret.w[1] = 2;
                ret.w[0] = 5;
            }
            return ret;
        case 10:
            if (CheckSolve() == 1) {
                if (D_800BEE20 != -1) {
                    StopSound(D_800BEE20);
                }
                task = FindProc(0x1020000, -1);
                ProcPostMessage(task, 19, 0);
                ProcPostEvent(10);
                CreatProc(func_8002BE84, 0x6000000);
                ret.w[1] = 0;
                ret.w[0] = 1;
                return ret;
            }
            GreyHiddenSquares();
            task = FindProc(0x1020000, -1);
            KillProc(task, 0);
            StartSolvePuzzle();
            ret.w[1] = 2;
            ret.w[0] = 10;
            return ret;
        case 33:
            if (D_800BEE20 != -1) {
                StopSound(D_800BEE20);
            }
            PlaySound(1);
            task = FindProc(0x1020000, -1);
            RevealPuzzle();
            ProcPostEvent(10);
            CreatProc(func_8002B904, 0x6000000);
            ret.w[1] = 0;
            ret.w[0] = 1;
            return ret;
        case 34:
            ret.w[1] = 0;
            ret.w[0] = 1;
            return ret;
        }
    }
    return ret;
}
