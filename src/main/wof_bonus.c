// wof_bonus.c -- the bonus round and the turn's status proc: the totals at the end, the bonus timer,
// the retraces, the bonus round itself, and the proc that lets the player spin, buy a vowel or solve
//
// The last part of the object wof_status.c opens (see there): from ShowWinTotalProc to StatusProc
// each function but the last ends off an 8-byte boundary with the next right after. CreditsProc, the
// function before ShowWinTotalProc, is the object's too, but its unit is held apart. This unit
// defines the object's data that lies after CreditsProc's.

#include "wof.h"

// the letters every bonus round gives
u8 givenLetters[] = "RSTLNE";

/*
=====================
ShowWinTotalProc

Shows the total of a bonus round won and a movie, then the credits.
=====================
*/
struct procResult_s ShowWinTotalProc(proc_t *proc) {
    s32 event;
    struct procResult_s ret;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    ret.w[1] = 1;
    ret.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            gameMode = 8;
            ShowTotal();
            MakeScreenObj(proc, 0, DrawBigNumber, 0x5050100);
            applause++;
            ret.w[0] = 30 / frameRetraces;
            return ret;
        case 46:
            CreatProc(CreditsProc, 0x6060000);
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        }
    }
    PlayMovieCorner(0, 46);
    ret.w[1] = 2;
    ret.w[0] = 46;
    return ret;
}

/*
=====================
BonusLostProc

The bonus puzzle was not solved: the camera, then ShowTotalProc.
=====================
*/
struct procResult_s BonusLostProc(proc_t *proc) {
    s32 event;
    struct procResult_s ret;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    ret.w[1] = 1;
    ret.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            ret.w[0] = 30 / frameRetraces;
            return ret;
        }
    }
    SetCameraView(20);
    CreatProc(ShowTotalProc, 0x6000000);
    ret.w[1] = 0;
    ret.w[0] = 0;
    return ret;
}

/*
=====================
BonusTimerProc

Shows the seconds left to solve the bonus puzzle.
=====================
*/
struct procResult_s BonusTimerProc(proc_t *proc) {
    s32 event;
    s32 tens;
    s32 ones;
    struct procResult_s result;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 33:
            bonusTimerImages[0].texture = bigDigitTextures[0];
            bonusTimerImages[0].width = bigDigitWidths[0];
            bonusTimerImages[1].texture = bigDigitTextures[0];
            bonusTimerImages[1].width = bigDigitWidths[0];
            ProcPostMessage(proc, 31, 0);
            result.w[0] = 30 / frameRetraces;
            return result;
        case 31:
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
    }
    tens = bonusTimeLeft / 10;
    ones = bonusTimeLeft % 10;
    bonusTimerImages[0].texture = bigDigitTextures[tens];
    bonusTimerImages[0].width = bigDigitWidths[tens];
    bonusTimerImages[1].texture = bigDigitTextures[ones];
    bonusTimerImages[1].width = bigDigitWidths[ones];
    return result;
}

/*
=====================
ShowRetracesProc

Shows frameRetraces as two digits.
=====================
*/
struct procResult_s ShowRetracesProc(proc_t *proc) {
    s32 busy;
    s32 tens;
    s32 ones;
    struct procResult_s result;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    result.w[1] = 1;
    result.w[0] = 0;
    do {
        busy = ProcGetMessage(proc);
    } while (busy != 0);
    tens = frameRetraces / 10;
    ones = frameRetraces % 10;
    retraceImages[0].texture = bigDigitTextures[tens];
    retraceImages[0].width = bigDigitWidths[tens];
    retraceImages[1].texture = bigDigitTextures[ones];
    retraceImages[1].width = bigDigitWidths[ones];
    return result;
}

/*
=====================
BonusWonProc

The bonus puzzle was solved: 25000, the lights and the celebration.
=====================
*/
struct procResult_s BonusWonProc(proc_t *proc) {
    s32 event;
    struct procResult_s result;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            applause = applause + 6;
            SetVannaAnim(1);
            StartBoardLights();
            StartCelebration();
            KillProcClass(0x5050200, -1, 1);
            players[curPlayer].total = players[curPlayer].total + 0x61A8;
            PlaySound(5);
            MakeScreenObj(proc, 0, func_8002842C, 0x5050000);
            result.w[0] = 320 / frameRetraces;
            return result;
        }
    }
    SetCameraView(20);
    CreatProc(ShowWinTotalProc, 0x6000000);
    result.w[1] = 0;
    result.w[0] = 1;
    return result;
}

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
            ClearBonusLetters();
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
            if (bonusLetterSlots[9].texture != 0) {
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
                MakeScreenObj(task, 0, DrawBonusTimer, 0x5050200);
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
                if (bonusLetterSlots[9].texture != 0) {
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
            while (i < 10 && bonusLetterSlots[i].texture != 0) {
                i++;
            }
            uncalled[curLetter - 65] = 32;
            bonusLetterSlots[i].texture = bonusLetterImages[curLetter - 65].unk_00;
            bonusLetterSlots[i].width = bonusLetterImages[curLetter - 65].width;
            bonusLetterSlots[i].height = bonusLetterImages[curLetter - 65].height;
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

/*
=====================
FlashPlayerStatus

Makes the status pictures of the player whose turn it is flash.
=====================
*/
void FlashPlayerStatus(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        playerStatusImages[i][0].flash = i == curPlayer;
        playerStatusImages[i][0].flashLeft = playerStatusImages[i][0].flashFrames;
        playerStatusImages[i][1].flash = i == curPlayer;
        playerStatusImages[i][1].flashLeft = playerStatusImages[i][1].flashFrames;
    }
}

/*
=====================
StatusProc

The proc of the status screen of a turn: the player chooses to spin, buy a vowel or solve, and the
player proc of the turn is told.
=====================
*/
struct procResult_s StatusProc(proc_t *proc) {
    s32 event;
    s32 i;
    struct procResult_s result;
    proc_t *handle;

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 27:
            inputCount++;
            UnflashActions();
            proc->data->cursor.index = curLetter - 48;
            actionImages[proc->data->cursor.index].flashLeft = actionImages[proc->data->cursor.index].flashFrames;
            break;
        case 8:
            UnflashActions();
            ClearCategory();
            shownJackpot = 0;
            ShowJackpot();
            SetScorePictures(0);
            for (i = 0; i < 26; i++) {
                letterImages[i].flash = 0;
            }
            result.w[1] = 2;
            result.w[0] = 40;
            return result;
        case 40:
            InitCategory();
            FlashPlayerStatus();
        case 3:
        case 9:
        case 10:
        case 11:
        case 24:
        case 31:
            inputCount++;
            UnflashActions();
            SetScorePictures(0);
            InitActionCursor(proc);
            actionImages[proc->data->cursor.index].flash = 1;
            proc->data->cursor.delay = 0;
            return result;
        case 15:
            inputCount++;
            UnflashActions();
            InitActionCursor(proc);
            InitCategory();
            shownJackpot = 0;
            ShowJackpot();
            actionImages[proc->data->cursor.index].flash = 1;
            proc->data->cursor.delay = 0;
            SetScorePictures(0);
        case 1:
            inputCount++;
            InitActionCursor(proc);
            FlashPlayerStatus();
            return result;
        case 21:
            inputCount++;
            UnflashActions();
            InitActionCursor(proc);
            ClearCategory();
            SetScorePictures(1);
            for (i = 0; i < 3; i++) {
                playerStatusImages[i][0].flash = 0;
                playerStatusImages[i][0].flashLeft = playerStatusImages[i][0].flashFrames;
                playerStatusImages[i][1].flash = 0;
                playerStatusImages[i][1].flashLeft = playerStatusImages[i][1].flashFrames;
            }
            result.w[1] = 2;
            if (gameOver != 0 || round == numRounds - 1) {
                result.w[0] = 42;
            } else {
                result.w[0] = 15;
            }
            return result;
        case 23:
            inputCount++;
            UnflashActions();
            result.w[1] = 2;
            result.w[0] = 24;
            return result;
        case 30:
            UnflashActions();
            result.w[1] = 2;
            result.w[0] = 32;
            finalSpin = 1;
            return result;
        case 42:
            inputCount++;
            StartBonusRound();
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        case 34:
            UnflashActions();
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
    }
    UnflashActions();
    handle = FindProc(curPlayer | 0x2000000, 0xFF0000FF);
    if (handle == 0) {
        FatalError("Status Proc: player proc does not exist\n");
    }
    if (finalSpin == 1) {
        actionImages[proc->data->cursor.index].flash = 0;
        return result;
    }
    if (players[curPlayer].controller == 4) {
        actionImages[proc->data->cursor.index].flash = 1;
        return result;
    }
    if ((buttonsPressed & 0xA000 & 0xFFFF) != 0) {
        inputCount++;
        proc->data->cursor.delay = 0;
        switch (proc->data->cursor.index) {
        case 0:
            if (canSpin != 0) {
                ProcPostEvent(12);
                result.w[1] = 2;
                result.w[0] = 3;
                return result;
            } else {
                PlaySound(1);
                return result;
            }
            break;
        case 1:
            if (canBuyVowel != 0) {
                ProcPostEvent(13);
                result.w[1] = 2;
                result.w[0] = 9;
                return result;
            } else {
                PlaySound(1);
                return result;
            }
            break;
        case 2:
            if (canSolve != 0) {
                ProcPostEvent(14);
                result.w[1] = 2;
                result.w[0] = 10;
                return result;
            } else {
                PlaySound(1);
                return result;
            }
            break;
        case 3:
            ProcPostEvent(38);
            func_8002FD14();
            return result;
        default:
            FatalError("Status Proc: button press invalid\n");
        }
    }
    if ((buttonsPressed & 2048 & 0xFFFF) != 0) {
        MoveCursorLeft(proc, 0);
    } else if ((buttonsPressed & 1024 & 0xFFFF) != 0) {
        MoveCursorRight(proc, 0, 1);
    } else if ((buttonsPressed & 512 & 0xFFFF) != 0) {
        MoveCursorLeft(proc, 0);
    } else if ((buttonsPressed & 256 & 0xFFFF) != 0) {
        MoveCursorRight(proc, 0, 1);
    } else if ((buttonsPressed & 0x8000 & 0xFFFF) != 0) {
        return result;
    } else if ((buttonsPressed & 0x4000 & 0xFFFF) != 0) {
        return result;
    }
    if (proc->data->cursor.delay <= 0) {
        if (playerPad.stick_y >= 41) {
            MoveCursorLeft(proc, 0);
        } else if (playerPad.stick_y < -40) {
            MoveCursorRight(proc, 0, 1);
        }
    } else {
        proc->data->cursor.delay -= frameRetraces;
    }
    if (proc->data->cursor.index < 0) {
        proc->data->cursor.index = 3;
    } else if (proc->data->cursor.index >= 4) {
        proc->data->cursor.index = 0;
    }
    actionImages[proc->data->cursor.index].flash = 1;
    return result;
}
