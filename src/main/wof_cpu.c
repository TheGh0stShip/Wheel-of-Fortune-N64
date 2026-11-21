// wof_cpu.c -- the machine's turn: its letters, its choice of solving, spinning or buying a vowel, its
// spin, vowel, solve and final spin, and its turn procs for the demo and a game
//
// PickHitLetter, CpuPickConsonant, CpuSpinProc, CpuBuyVowelProc, CpuFinalSpinTurnProc and AddDemoCpu
// each end off an 8-byte boundary with the next function right after, which happens only inside an
// object, and CpuPickVowel's read-only items run on into CpuChooseAction's with no 8-byte boundary
// between. The joins after CpuChooseAction, CpuSolveProc and CpuTurnProc rest on the RCS premise (every
// object from 0x8000BAA8 on opens its read-only data with an RCS run, which the project accepts): no
// run lies where an object starting there would need one. Its read-only data opens with the RCS run at
// 0x800011B0, which could open an object starting after InitPlayers, InitCpuLetters or PickMissLetter;
// where it ends after AddCpu the text does not say (the RCS run at 0x800014B8 opens the next object
// after AddCpu or one of the movie functions after it).

#include "wof.h"

// The #ident line of the system header this object included: the original assembler put the string
// into the read-only data, which it opens. The header is not in this tree, so its line stands here.
#ident "$Revision: 1.17 $"

/*
=====================
PickHitLetter

The last letter of a string that is in the puzzle, or else PickMissLetter's.
=====================
*/
s32 PickHitLetter(u8 *letters) {
    s32 i;
    s32 len;
    u8 c;

    c = ' ';
    len = StrLen(letters);
    for (i = 0; i < len; i++) {
        if (CountLetter(letters[i]) > 0) {
            c = letters[i];
            break;
        }
    }
    if (c == ' ') {
        c = PickMissLetter(letters);
    }
    return c;
}

/*
=====================
CpuPickConsonant

The machine's consonant: a right one with the chance of its skill.
=====================
*/
s32 CpuPickConsonant(f32 skill, proc_t *proc) {
    f32 roll;
    u8 result;

    RemoveCalledLetters(cpuConsonants);
    roll = Random(100);
    roll = roll / 100.0f;
    if (roll < skill) {
        result = PickHitLetter(cpuConsonants);
    } else {
        result = PickMissLetter(cpuConsonants);
        if (result == 32) {
            result = PickHitLetter(cpuConsonants);
        }
    }
    return result;
}

/*
=====================
CpuPickVowel

The machine's vowel: a right one with the chance of its skill.
=====================
*/
s32 CpuPickVowel(f32 skill) {
    f32 roll;
    u8 result;

    RemoveCalledLetters(cpuVowels);
    roll = (f32)Random(100);
    roll = roll / 100.0f;
    if (roll < skill) {
        result = PickHitLetter(cpuVowels);
    } else {
        result = PickMissLetter(cpuVowels);
        if (result == 32) {
            result = PickHitLetter(cpuVowels);
        }
    }
    return result;
}

/*
=====================
CpuChooseAction

The machine decides to solve, spin or buy a vowel.
=====================
*/
void CpuChooseAction(proc_t *proc) {
    proc_t *task;
    s32 zero;  /* NOTE: set to 0 and never read */
    f32 score;
    f32 roll;
    f32 done;

    zero = 0;
    done = CheckPercentDone();
    task = FindProc(0x5000000, -1);
    if (canSolve != 0) {
        if (jackpotWon != 0) {
            if (done > 0.6) {
                curLetter = 50;
                ProcPostMessage(proc, PRC_EVENT_SOLVE_SELECTED, 0);
                ProcPostMessage(task, PRC_EVENT_COMPUTER_CHANGED, 0);
                return;
            }
        }
        if (done > 0.7 || canSpin == 0) {
            curLetter = 50;
            ProcPostMessage(proc, PRC_EVENT_SOLVE_SELECTED, 0);
            ProcPostMessage(task, PRC_EVENT_COMPUTER_CHANGED, 0);
            return;
        }
    }
    if (canSpin != 0) {
        roll = (f32)Random(100);
        roll = roll / 100.0f;
        score = (f32)StrLen(cpuConsonants);
        score = score / 21.0f;
        score = score * 0.15;
        score = score + roll;
        switch (GetUncalledKinds()) {
        case 4:
            if (score < proc->data->playerProc.skill || players[curPlayer].score < 250) {
                curLetter = 48;
                ProcPostMessage(proc, PRC_EVENT_SPIN_SELECTED, 0);
            } else {
                curLetter = 49;
                ProcPostMessage(proc, PRC_EVENT_SVOWEL_SELECTED, 0);
            }
            break;
        case 3:
            curLetter = 48;
            ProcPostMessage(proc, PRC_EVENT_SPIN_SELECTED, 0);
            break;
        case 2:
            curLetter = 49;
            ProcPostMessage(proc, PRC_EVENT_SVOWEL_SELECTED, 0);
            break;
        }
    } else if (canBuyVowel != 0) {
        if (StrLen(cpuVowels) != 0) {
            curLetter = 49;
            ProcPostMessage(proc, PRC_EVENT_SVOWEL_SELECTED, 0);
        } else {
            curLetter = 48;
            ProcPostMessage(proc, PRC_EVENT_SPIN_SELECTED, 0);
        }
    }
    ProcPostMessage(task, PRC_EVENT_COMPUTER_CHANGED, 0);
}

/*
=====================
CpuSpinProc

The machine spins.
=====================
*/
struct procResult_s CpuSpinProc(proc_t *proc) {
    struct procResult_s result;
    proc_t *task;
    obj_t *target;
    s32 event;

    result.w[1] = 1;
    result.w[0] = 0;
    if (proc->data->playerProc.player != curPlayer) {
        ProcClearMessages(proc);
        return result;
    }
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == PRC_EVENT_NULL) {
            break;
        }
        switch (event) {
        case PRC_EVENT_INIT:
            SetGameView(0, 1);
            task = CreatProc(WheelSpinProc, 0x4000000);
            target = FindObj(0x4010000, 0xFFFF0000);
            task->data->wheelSpin.wheel = target;
            task->data->wheelSpin.speed = (f32)(guRandom() % 50 + 100);
            if ((f64)task->data->wheelSpin.speed > 80.0) {
                ProcPostMessage(proc, PRC_EVENT_WHEEL_LONG_SPIN, 0);
                result.w[1] = 1;
                result.w[0] = 30 / frameRetraces;
                return result;
            } else {
                result.w[1] = 2;
                result.w[0] = -1;
                return result;
            }
            break;
        case PRC_EVENT_WHEEL_LONG_SPIN:
            if (Random(100) >= 76) {
                SetGameView(15, 1);
            } else {
                SetGameView(3, 1);
            }
            result.w[1] = 2;
            result.w[0] = PRC_EVENT_WHEEL_ALMOST_STOPPED;
            return result;
            break;
        case PRC_EVENT_WHEEL_ALMOST_STOPPED:
            SetGameView(0, 1);
            result.w[1] = 2;
            result.w[0] = PRC_EVENT_WHEEL_STOPPED;
            return result;
            break;
        case PRC_EVENT_WHEEL_STOPPED:
            target = FindObj(0x4010000, 0xFFFF0000);
            ApplyWedge(0);
            if (GetWedgeValue() == -1) {
                SetContestantsStill();
                SetGameView(0, 1);
                if (LoseTurn() != 0) {
                    ProcPostEvent(PRC_EVENT_DONE_SPINING);
                    ProcPostEvent(PRC_EVENT_COMPUTER_DONE);
                }
                result.w[1] = 0;
                result.w[0] = 0;
                return result;
            } else {
                if (GetWedgeValue() == -2) {
                    SetContestantsStill();
                    SetGameView(0, 1);
                    if (MustLoseTurn() != 0) {
                        PlayMovieCorner(12, PRC_EVENT_VIDEO_DONE);
                        result.w[1] = 2;
                        result.w[0] = PRC_EVENT_VIDEO_DONE;
                        return result;
                    }
                    LoseTurn();
                    result.w[1] = 0;
                    result.w[0] = 0;
                    return result;
                }
            }
            PlayContestantAnims();
            SetGameView(3, 1);
            StartCpuLetterPick(CpuPickConsonant(proc->data->playerProc.skill, proc) & 255);
            ProcPostMessage(proc, PRC_EVENT_DONE_SELECTING, 0);
            result.w[1] = 1;
            result.w[0] = 60 / frameRetraces;
            return result;
        case PRC_EVENT_VIDEO_DONE:
            LoseTurn();
            ProcPostEvent(PRC_EVENT_DONE_SPINING);
            ProcPostEvent(PRC_EVENT_COMPUTER_DONE);
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        case PRC_EVENT_DONE_SELECTING:
            PlaySound(players[curPlayer].letterSounds + (curLetter - 65));
            ProcPostMessage(proc, PRC_EVENT_DONE_SAYING, 0);
            result.w[1] = 1;
            result.w[0] = 30 / frameRetraces;
            return result;
        case PRC_EVENT_DONE_SAYING:
            ShowJackpot();
            task = FindProc(0x5010000, -1);
            ProcPostMessage(task, PRC_EVENT_COMPUTER_SELECTED, 0);
            if (CallLetter(curLetter, 0) > 0) {
                ShowLetter(curLetter);
                task = CreatProc(LightLetterProc, 0x1000000);
                task->data->lightLetter.letter = curLetter;
                result.w[1] = 2;
                result.w[0] = PRC_EVENT_DONE_REVEALING;
                return result;
            } else {
                PlaySound(1);
                if (LoseTurn() != 0) {
                    ProcPostEvent(PRC_EVENT_DONE_SPINING);
                    ProcPostEvent(PRC_EVENT_COMPUTER_DONE);
                }
                result.w[1] = 0;
                result.w[0] = 0;
                return result;
            }
            break;
        case PRC_EVENT_DONE_REVEALING:
            if (GetWedgeValue() == -3) {
                jackpotWon = 1;
            }
            ProcPostEvent(PRC_EVENT_COMPUTER_DONE);
            ProcPostEvent(PRC_EVENT_DONE_SPINING);
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        case PRC_EVENT_DEMO_TIMEOUT:
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    return result;
}

/*
=====================
CpuBuyVowelProc

The machine buys a vowel.
=====================
*/
struct procResult_s CpuBuyVowelProc(proc_t *proc) {
    struct procResult_s ret;
    proc_t *task;
    s32 unused;  /* NOTE: unused in the original */
    s32 event;

    ret.w[1] = 1;
    ret.w[0] = 0;
    if (proc->data->playerProc.player != curPlayer) {
        ProcClearMessages(proc);
        return ret;
    }
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == PRC_EVENT_NULL) {
            break;
        }
        switch (event) {
        case PRC_EVENT_INIT:
            if (players[curPlayer].score < 250) {
                ProcPostMessage(proc, PRC_EVENT_NOT_ENOUGH, 0);
                PlaySound(1);
                ret.w[1] = 1;
                ret.w[0] = 30 / frameRetraces;
                return ret;
            } else {
                SetGameView(3, 1);
                StartCpuLetterPick(CpuPickVowel(proc->data->playerProc.skill) & 255);
                ProcPostMessage(proc, PRC_EVENT_DONE_SELECTING, 0);
                ret.w[1] = 1;
                ret.w[0] = 60 / frameRetraces;
                return ret;
            }
            break;
        case PRC_EVENT_DONE_SELECTING:
            PlaySound(players[curPlayer].letterSounds + (curLetter - 'A'));
            ProcPostMessage(proc, PRC_EVENT_DONE_SAYING, 0);
            ret.w[1] = 1;
            ret.w[0] = 30 / frameRetraces;
            return ret;
        case PRC_EVENT_DONE_SAYING:
            task = FindProc(0x5010000, -1);
            ProcPostMessage(task, PRC_EVENT_COMPUTER_SELECTED, 0);
            if (CallLetter(curLetter, 1) > 0) {
                ShowLetter(curLetter);
                task = CreatProc(LightLetterProc, 0x1000000);
                task->data->lightLetter.letter = curLetter;
                ret.w[1] = 2;
                ret.w[0] = PRC_EVENT_DONE_REVEALING;
            } else {
                PlaySound(1);
                if (LoseTurn() != 0) {
                    ProcPostEvent(PRC_EVENT_DONE_VOWEL);
                    ProcPostEvent(PRC_EVENT_COMPUTER_DONE);
                }
                ret.w[1] = 0;
                ret.w[0] = 0;
                return ret;
            }
            break;
        case PRC_EVENT_NOT_ENOUGH:
            ProcPostEvent(PRC_EVENT_DONE_VOWEL);
            PlaySound(150);
            // RULE-EXCEPTION: R25, no prototype in scope: retail passes the 0.8 as a double
            StartRumble(players[curPlayer].controller, 30, 0.8);
            LoseTurn();
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        case PRC_EVENT_DONE_REVEALING:
            ProcPostEvent(PRC_EVENT_COMPUTER_DONE);
            ProcPostEvent(PRC_EVENT_DONE_VOWEL);
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        case PRC_EVENT_DEMO_TIMEOUT:
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        }
    }
    return ret;
}

/*
=====================
CpuSolveProc

The machine solves.
=====================
*/
struct procResult_s CpuSolveProc(proc_t *proc) {
    struct procResult_s result;
    proc_t *task;
    s32 unused;  /* NOTE: unused in the original */
    s32 event;

    result.w[1] = 1;
    result.w[0] = 0;
    if (proc->data->playerProc.player != curPlayer) {
        ProcClearMessages(proc);
        return result;
    }
    task = FindProc(0x1020000, -1);
    while ((event = ProcGetMessage(proc)) != PRC_EVENT_NULL) {
        switch (event) {
        case PRC_EVENT_INIT:
            StartSolvePuzzle();
            SetGameView(3, 1);
            result.w[1] = 2;
            result.w[0] = PRC_EVENT_DONE_SELECTING;
            return result;
        case PRC_EVENT_DONE_SELECTING:
            if (CheckSolve() == 1) {
                ProcPostMessage(task, PRC_EVENT_HIGHLIGHT_ALL, 0);
                ProcPostEvent(PRC_EVENT_COMPUTER_DONE);
                ProcPostEvent(PRC_EVENT_DONE_SOLVE);
                result.w[1] = 0;
                result.w[0] = 0;
            } else {
                ProcPostMessage(task, PRC_EVENT_CLEAR_GUESSED, 0);
                PlaySound(1);
                if (LoseTurn() != 0) {
                    ProcPostEvent(PRC_EVENT_DONE_SOLVE);
                    ProcPostEvent(PRC_EVENT_COMPUTER_DONE);
                }
                result.w[1] = 0;
                result.w[0] = 0;
                return result;
            }
            break;
        case PRC_EVENT_DEMO_TIMEOUT:
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    return result;
}

/*
=====================
CpuFinalSpinTurnProc

The machine's turn in the final spin.
=====================
*/
struct procResult_s CpuFinalSpinTurnProc(proc_t *proc) {
    struct procResult_s result;
    proc_t *task;
    s32 unused;  /* NOTE: unused in the original */
    s32 event;
    f32 ratio;

    result.w[1] = 1;
    result.w[0] = 0;
    if (proc->data->playerProc.player != curPlayer) {
        ProcClearMessages(proc);
        return result;
    }
    task = FindProc(0x5000000, -1);
    while ((event = ProcGetMessage(proc)) != PRC_EVENT_NULL) {
        switch (event) {
        case PRC_EVENT_INIT:
            SetGameView(3, 1);
            switch (GetHiddenKinds()) {
            case 4:
                if (Random(100) >= 11) {
                    StartCpuLetterPick(CpuPickConsonant(proc->data->playerProc.skill, proc) & 255);
                } else {
                    StartCpuLetterPick(CpuPickVowel(proc->data->playerProc.skill) & 255);
                }
                break;
            case 2:
                StartCpuLetterPick(CpuPickVowel(proc->data->playerProc.skill) & 255);
                break;
            case 3:
                StartCpuLetterPick(CpuPickConsonant(proc->data->playerProc.skill, proc) & 255);
                break;
            }
            ProcPostMessage(proc, PRC_EVENT_DONE_SELECTING, 0);
            result.w[1] = 1;
            result.w[0] = 60 / frameRetraces;
            return result;
            break;
        case PRC_EVENT_DONE_SELECTING:
            PlaySound(players[curPlayer].letterSounds + (curLetter - 65));
            ProcPostMessage(proc, PRC_EVENT_DONE_SAYING, 0);
            result.w[1] = 1;
            result.w[0] = 30 / frameRetraces;
            return result;
        case PRC_EVENT_DONE_SAYING:
            task = FindProc(0x5010000, -1);
            ProcPostMessage(task, PRC_EVENT_COMPUTER_SELECTED, 0);
            if (CallLetter(curLetter, 2) > 0) {
                ShowLetter(curLetter);
                task = CreatProc(LightLetterProc, 0x1000000);
                task->data->lightLetter.letter = curLetter;
                result.w[1] = 2;
                result.w[0] = PRC_EVENT_DONE_REVEALING;
                return result;
            } else {
                PlaySound(1);
                LoseTurn();
                ProcPostEvent(PRC_EVENT_COMPUTER_DONE);
                ProcPostEvent(PRC_EVENT_DONE_SPEEDUP);
                ProcPostMessage(task, PRC_EVENT_DONE_SPEEDUP, 0);
                result.w[1] = 0;
                result.w[0] = 0;
                return result;
            }
        case PRC_EVENT_DONE_REVEALING:
            SetScorePictures(0);
            StartSolveTimer();
            ratio = CheckPercentDone();
            if (ratio > 0.7) {
                task = CreatProc(CpuSolveProc, proc->data->playerProc.player | 0x2000300);
                task->data->playerProc.player = proc->data->playerProc.player;
                task->data->playerProc.skill = proc->data->playerProc.skill;
                result.w[1] = 2;
                result.w[0] = PRC_EVENT_DONE_SOLVE;
                return result;
            } else {
                result.w[1] = 1;
                result.w[0] = 0;
                return result;
            }
        case PRC_EVENT_SOLVE_TIMEOUT:
            PlaySound(1);
        case PRC_EVENT_DONE_SOLVE:
            if (CheckSolve() != 1) {
                LoseTurn();
            }
            ProcPostEvent(PRC_EVENT_COMPUTER_DONE);
            ProcPostEvent(PRC_EVENT_DONE_SPEEDUP);
            ProcPostMessage(task, PRC_EVENT_DONE_SPEEDUP, 0);
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        case PRC_EVENT_DEMO_TIMEOUT:
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    return result;
}

/*
=====================
CpuTurnProc

The turn of the machine: makes the procs of its steps.
=====================
*/
struct procResult_s CpuTurnProc(proc_t *proc) {
    s32 event;
    struct procResult_s ret;
    proc_t *task;

    ret.w[1] = 1;
    ret.w[0] = 0;
    if (proc->data->playerProc.player != curPlayer) {
        while ((event = ProcGetMessage(proc)) != PRC_EVENT_NULL) {
            switch (event) {
            case PRC_EVENT_DEMO_TIMEOUT:
                ret.w[1] = 0;
                ret.w[0] = 0;
                return ret;
            case PRC_EVENT_BONUS_ROUND:
                ret.w[1] = 0;
                ret.w[0] = 0;
                return ret;
            }
        }
        return ret;
    }
    while ((event = ProcGetMessage(proc)) != PRC_EVENT_NULL) {
        switch (event) {
        case PRC_EVENT_FREE_SPIN_USED:
            PlaySound(players[curPlayer].freeSpinSound);
            players[curPlayer].freeSpin = 0;
            /* fallthrough */
        case PRC_EVENT_DONE_SPINING:
        case PRC_EVENT_DONE_VOWEL:
        case PRC_EVENT_DONE_SOLVE:
        case PRC_EVENT_DONE_SPEEDUP:
            SetGameView(3, 1);
            task = FindProc(0x5000000, -1);
            ProcPostMessage(task, PRC_EVENT_COMPUTER_DONE, 0);
            if (CheckSolved(1) == 1) {
                ProcPostMessage(task, PRC_EVENT_ROUND_OVER, 0);
                StartBoardLights();
                applause += 3;
                PlaySound(5);
                task = CreatProc(RoundOverProc, proc->data->playerProc.player | 0x2000500);
                task->data->playerProc.player = proc->data->playerProc.player;
                if (gameOver != 0 || round == numRounds - 1) {
                    ret.w[1] = 0;
                    ret.w[0] = 0;
                } else {
                    ret.w[1] = 2;
                    ret.w[0] = PRC_EVENT_START_ROUND;
                }
                return ret;
            }
            if (vowelsOnlyAnnounced == 0 && GetHiddenKinds() == 2) {
                vowelsOnlyAnnounced = 1;
                PlaySound(6);
            }
            ProcPostMessage(proc, PRC_EVENT_COMPUTER_SELECT, 0);
            ret.w[1] = 1;
            ret.w[0] = 20 / frameRetraces;
            return ret;
        case PRC_EVENT_INIT:
            ret.w[1] = 2;
            ret.w[0] = PRC_EVENT_START_FIRST_ROUND;
            return ret;
        case PRC_EVENT_START_FIRST_ROUND:
            InitBoard();
            ProcPostMessage(proc, PRC_EVENT_NEXT_PLAYER, 0);
            SetGameView(3, 1);
            ret.w[1] = 1;
            ret.w[0] = 60 / frameRetraces;
            return ret;
        case PRC_EVENT_NEXT_PLAYER:
        case PRC_EVENT_DONE_FINAL_SPIN:
            ProcPostEvent(PRC_EVENT_COMPUTER_DONE);
            if (finalSpin == 1) {
                task = CreatProc(CpuFinalSpinTurnProc, proc->data->playerProc.player | 0x2030400);
                task->data->playerProc.player = proc->data->playerProc.player;
                task->data->playerProc.skill = proc->data->playerProc.skill;
                ret.w[1] = 2;
                ret.w[0] = PRC_EVENT_DONE_SPEEDUP;
                return ret;
            }
            ProcPostMessage(proc, PRC_EVENT_COMPUTER_SELECT, 0);
            ret.w[1] = 1;
            ret.w[0] = 30 / frameRetraces;
            SetGameView(3, 1);
            applause++;
            return ret;
        case PRC_EVENT_NEXT_ROUND:
            ProcPostEvent(PRC_EVENT_COMPUTER_DONE);
            if (finalSpin == 1) {
                task = CreatProc(CpuFinalSpinTurnProc, proc->data->playerProc.player | 0x2030400);
                task->data->playerProc.player = proc->data->playerProc.player;
                task->data->playerProc.skill = proc->data->playerProc.skill;
                ret.w[1] = 2;
                ret.w[0] = PRC_EVENT_DONE_SPEEDUP;
                return ret;
            }
            ProcPostMessage(proc, PRC_EVENT_SPIN_SELECTED, 0);
            ret.w[1] = 1;
            ret.w[0] = 60 / frameRetraces;
            SetGameView(3, 1);
            return ret;
        case PRC_EVENT_COMPUTER_SELECT:
            if (finalSpin == 1) {
                task = CreatProc(CpuFinalSpinTurnProc, proc->data->playerProc.player | 0x2030400);
                task->data->playerProc.player = proc->data->playerProc.player;
                task->data->playerProc.skill = proc->data->playerProc.skill;
                ret.w[1] = 2;
                ret.w[0] = PRC_EVENT_DONE_SPEEDUP;
                return ret;
            }
            CpuChooseAction(proc);
            ret.w[1] = 1;
            ret.w[0] = 60 / frameRetraces;
            return ret;
        case PRC_EVENT_SPIN_SELECTED:
            if (guRandom() % 100 < 33) {
                PlaySound(players[curPlayer].spinSound);
            }
            jackpotWon = 0;
            task = FindProc(0x5000000, -1);
            ProcPostMessage(task, PRC_EVENT_COMPUTER_SELECTED, 0);
            task = CreatProc(CpuSpinProc, proc->data->playerProc.player | 0x2000100);
            task->data->playerProc.player = proc->data->playerProc.player;
            task->data->playerProc.skill = proc->data->playerProc.skill;
            ret.w[1] = 2;
            ret.w[0] = PRC_EVENT_DONE_SPINING;
            return ret;
        case PRC_EVENT_SVOWEL_SELECTED:
            PlaySound(players[curPlayer].buyVowelSound);
            jackpotWon = 0;
            task = FindProc(0x5000000, -1);
            ProcPostMessage(task, PRC_EVENT_COMPUTER_SELECTED, 0);
            task = CreatProc(CpuBuyVowelProc, proc->data->playerProc.player | 0x2000200);
            task->data->playerProc.player = proc->data->playerProc.player;
            task->data->playerProc.skill = proc->data->playerProc.skill;
            ret.w[1] = 2;
            ret.w[0] = PRC_EVENT_DONE_VOWEL;
            return ret;
        case PRC_EVENT_SOLVE_SELECTED:
            PlaySound(players[curPlayer].solveSound);
            task = FindProc(0x5000000, -1);
            ProcPostMessage(task, PRC_EVENT_COMPUTER_SELECTED, 0);
            task = CreatProc(CpuSolveProc, proc->data->playerProc.player | 0x2000300);
            task->data->playerProc.player = proc->data->playerProc.player;
            task->data->playerProc.skill = proc->data->playerProc.skill;
            ret.w[1] = 2;
            ret.w[0] = PRC_EVENT_DONE_SOLVE;
            return ret;
        case PRC_EVENT_USE_FREE_SPIN:
            jackpotWon = 0;
            task = FindProc(0x5000000, -1);
            curLetter = '3';
            ProcPostMessage(task, PRC_EVENT_COMPUTER_CHANGED, 1);
            ProcPostMessage(proc, PRC_EVENT_FREE_SPIN_USED, 0);
            ret.w[1] = 1;
            ret.w[0] = 60 / frameRetraces;
            return ret;
        case PRC_EVENT_START_ROUND:
            NextRound();
            if (proc->data->playerProc.player != curPlayer) {
                ret.w[1] = 2;
                ret.w[0] = -1;
            } else {
                ret.w[1] = 1;
                ret.w[0] = 0;
            }
            return ret;
        case PRC_EVENT_GAME_TIMEOUT:
            ret.w[1] = 2;
            ret.w[0] = PRC_EVENT_DONE_FINAL_SPIN;
            return ret;
        case PRC_EVENT_DEMO_TIMEOUT:
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        }
    }
    return ret;
}

/*
=====================
AddDemoCpu

A machine turn proc for the demo, of skill 0.65.
=====================
*/
void AddDemoCpu(s32 player) {
    proc_t *task;
    s32 unused;   /* NOTE: unused in the original */
    s32 unused2;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    task = CreatProc(CpuTurnProc, player | 0x2030000);
    task->data->playerProc.player = player;
    task->data->playerProc.skill = 0.65f;
    players[player].controller = 4;
    SetContestantSounds(player);
}

/*
=====================
AddCpu

A machine turn proc of the skill chosen.
=====================
*/
void AddCpu(s32 player) {
    proc_t *task;
    s32 unused;   /* NOTE: unused in the original */
    s32 unused2;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    task = CreatProc(CpuTurnProc, player | 0x2030000);
    task->data->playerProc.player = player;
    task->data->playerProc.skill = cpuSkill;
}
