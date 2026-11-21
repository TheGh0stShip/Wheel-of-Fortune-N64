// BonusRoundProc.c -- the bonus round: the given letters, three consonants and a vowel, then the
// solve

#include "wof.h"

/*
=====================
BonusRoundProc

The bonus round: the given letters, three consonants and a vowel, then the solve.
=====================
*/
struct procResult_s BonusRoundProc(proc_t *proc) {
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
            bonusMusicSlot = -1;
            for (i = 0; i < 5; i++) {
                D_800B61B0[i] = 0;
            }
            bonusConsonants = 0;
            bonusVowels = 0;
            func_8002B054();
            InitCategory();
            ret.w[1] = 1;
            ret.w[0] = 60 / frameRetraces;
            ProcPostMessage(proc, 11, 0);
            return ret;
        case 11:
            if (lightDir < 0) {
                PlayMovieCorner(9, 44);
            } else {
                PlayMovie(9, 44, 180, 20);
            }
            ret.w[1] = 2;
            ret.w[0] = 44;
            return ret;
        case 44:
            for (i = 0; givenLetters[i] != 0; i++) {
                uncalled[givenLetters[i] - 65] = 32;
                ShowLetter(givenLetters[i]);
            }
            task = CreatProc(LightTextProc, 0x1000000);
            task->data->lightText.row = 0;
            task->data->lightText.col = 0;
            task->data->lightText.text = givenLetters;
            ret.w[1] = 2;
            ret.w[0] = 6;
            return ret;
        case 6:
            if (D_8005BE00[9].texture != 0) {
                if (CheckSolved(0) == 1) {
                    ProcPostEvent(10);
                    CreatProc(BonusWonProc, 0x6000000);
                    ret.w[1] = 0;
                    ret.w[0] = 1;
                    return ret;
                }
                bonusMusicSlot = PlaySound(22);
                StartSolveTimer();
                StartSolvePuzzle();
                task = CreatProc(BonusTimerProc, 0x5050200);
                MakeScreenObj(task, 0, func_80028554, 0x5050200);
                ret.w[1] = 2;
                ret.w[0] = 10;
                return ret;
            }
            if (lightDir < 0) {
                PlayMovieCorner(10, 0);
            } else {
                PlayMovie(10, 0, 180, 20);
            }
            StartLetterPick();
            ret.w[1] = 2;
            ret.w[0] = 5;
            return ret;
        case 5:
            if (IsVowel(curLetter) != 0) {
                if (D_8005BE00[9].texture != 0) {
                    PlaySound(1);
                    StartLetterPick();
                    ret.w[1] = 2;
                    ret.w[0] = 5;
                    return ret;
                } else {
                    bonusVowels++;
                    i = 9;
                }
            } else {
                if (bonusConsonants >= 3) {
                    PlaySound(1);
                    StartLetterPick();
                    ret.w[1] = 2;
                    ret.w[0] = 5;
                    return ret;
                }
                bonusConsonants++;
                i = 6;
            }
            while (i < 10 && D_8005BE00[i].texture != 0) {
                i++;
            }
            uncalled[curLetter - 65] = 32;
            D_8005BE00[i].texture = D_8005BCC8[curLetter - 65].unk_00;
            D_8005BE00[i].width = D_8005BCC8[curLetter - 65].width;
            D_8005BE00[i].height = D_8005BCC8[curLetter - 65].height;
            ShowLetter(curLetter);
            D_800B61AA[i] = curLetter;
            if (StrLen(D_800B61B0) == 4) {
                task = CreatProc(LightTextProc, 0x1000000);
                task->data->lightText.row = 0;
                task->data->lightText.col = 0;
                task->data->lightText.text = D_800B61B0;
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
                if (bonusMusicSlot != -1) {
                    StopSound(bonusMusicSlot);
                }
                task = FindProc(0x1020000, -1);
                ProcPostMessage(task, 19, 0);
                ProcPostEvent(10);
                CreatProc(BonusWonProc, 0x6000000);
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
            if (bonusMusicSlot != -1) {
                StopSound(bonusMusicSlot);
            }
            PlaySound(1);
            task = FindProc(0x1020000, -1);
            RevealPuzzle();
            ProcPostEvent(10);
            CreatProc(BonusLostProc, 0x6000000);
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
