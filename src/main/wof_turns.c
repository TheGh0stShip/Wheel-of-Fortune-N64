// wof_turns.c -- the turns: losing one, the next turn and round, the winner, the camera of a turn, the
// end of a round, and a person's spin, vowel, solve and final spin, with the players' turn procs
//
// The object starts after the 4-byte gap that ends CreateCamera. Its read-only data opens with the RCS
// run at 0x80000E98, which could open an object starting after LoseTurn, NextTurn, NextRound or
// FindWinner instead; that it opens at the gap, so that LoseTurn to FindWinner are this object's, rests
// on the RCS premise (every object from 0x8000BAA8 on opens its read-only data with an RCS run, which
// the project accepts), and so do the joins after WinnerProc, SpinProc and SolveProc: no run lies where
// an object starting there would need one. Inside, MustLoseTurn, SetGameView, RoundOverProc,
// BuyVowelProc, FinalSpinTurnProc, PlayerTurnProc and AddPlayer end off an 8-byte boundary with the next
// function right after, which happens only inside an object, and AdjustCameraProc's read-only items run
// on into SetGameView's with no 8-byte boundary between. Its data runs from views to playerViews with no
// gap; pointerAngles, between them, is this object's too. Where it ends after InitPlayers the text does
// not say: the RCS run at 0x800011B0 opens the next object after InitPlayers, InitCpuLetters or
// PickMissLetter.

#include "wof.h"
#include "rumble.h"

// The #ident line of the system header this object included: the original assembler put the string
// into the read-only data, which it opens. The header is not in this tree, so its line stands here.
#ident "$Revision: 1.17 $"

/*
=====================
LoseTurn

The turn passes, unless the player holds a free spin, who is asked (PRC_EVENT_USE_FREE_SPIN) and
keeps it.
=====================
*/
s32 LoseTurn(void) {
    proc_t *handle;

    if (players[curPlayer].freeSpin != 0 && finalSpin == 0) {
        ProcPostMessageClass(PRC_EVENT_USE_FREE_SPIN, curPlayer | 0x2000000, 0xFF0000FF, 1);
        return 0;
    }
    NextPlayer(0);
    LightPlayer(curPlayer);
    handle = FindProc(curPlayer | 0x2000000, 0xFF0000FF);
    ProcPostMessage(handle, PRC_EVENT_NEXT_PLAYER, 0);
    handle = FindProc(0x5000000, -1);
    ProcPostMessage(handle, PRC_EVENT_NEXT_PLAYER, 0);
    return 1;
}

/*
=====================
NextTurn

The turn passes to the next player.
=====================
*/
void NextTurn(void) {
    proc_t *handle;

    NextPlayer(0);
    LightPlayer(curPlayer);
    handle = FindProc(curPlayer | 0x2000000, 0xFF0000FF);
    ProcPostMessage(handle, PRC_EVENT_NEXT_PLAYER, 0);
    handle = FindProc(0x5000000, -1);
    ProcPostMessage(handle, PRC_EVENT_NEXT_PLAYER, 0);
    return;
}

/*
=====================
MustLoseTurn

0 when the player holds a free spin outside the final spin.
=====================
*/
s32 MustLoseTurn(void) {
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    if (players[curPlayer].freeSpin != 0 && finalSpin == 0) {
        return 0;
    }
    return 1;
}

/*
=====================
NextRound

Starts the next round.
=====================
*/
void NextRound(void) {
    proc_t *handle;

    NextPlayer(1);
    StartRound();
    LightPlayer(curPlayer);
    handle = FindProc(curPlayer | 0x02000000, 0xFF0000FF);
    ProcPostMessage(handle, PRC_EVENT_NEXT_ROUND, 0);
    ProcPostEvent(PRC_EVENT_NEXT_ROUND);
    InitBoard();
    InitCpuLetters();
}

/*
=====================
FindWinner

The player with the most money takes the turn and is shown.
=====================
*/
void FindWinner(void) {
    s32 i;
    s32 max;

    max = 0;
    curPlayer = 0;
    for (i = 0; i < 3; i++) {
        if (players[i].total > max) {
            max = players[i].total;
            curPlayer = i;
        }
    }
    UnlightPlayers();
    FlashScore(curPlayer);
}

view_t views[21] = {
    { 39, 350, 11, -76.0f, 227.0f, 0.0f, NULL, 0 },
    { 136, 298, 667, -11.0f, 377.0f, 0.0f, NULL, 0 },
    { -492, 234, -507, -11.0f, 224.0f, 0.0f, NULL, 0 },
    { -269, 75, -162, 0.0f, 0.0f, 0.0f, NULL, 0 },
    { 31, 350, 28, -76.0f, 205.0f, 0.0f, NULL, 0 },
    { 16, 350, 35, -76.0f, 181.0f, 0.0f, NULL, 0 },
    { -565, 544, -1192, -7.244f, -153.173f, -22.122f, NULL, 0 },
    { -378, 150, -862, -16.5f, 204.5f, 0.0f, NULL, 0 },
    { -565, 50, -1255, -7.5f, 273.5f, 0.0f, NULL, 0 },
    { -798, 50, -775, -3.0f, 269.5f, 0.0f, NULL, 0 },
    { 0, 0, 1000, 0.0f, 0.0f, 0.0f, NULL, 0 },
    { 0, 0, 0, 0.0f, 0.0f, 0.0f, fastSpinPath1, 241 },
    { 0, 0, 0, 0.0f, 0.0f, 0.0f, gameStartPath, 301 },
    { 0, 0, 0, 0.410065f, 0.241922f, 0.879387f, nextRoundPath, 91 },
    { 0, 0, 0, 0.0f, 0.0f, 0.0f, view14Path, 91 },
    { 0, 0, 0, 0.0f, 0.0f, 0.0f, fastSpinPath2, 241 },
    { 0, 0, 0, 0.0f, 0.0f, 0.0f, view16Path, 181 },
    { -183, 150, -581, -4.5f, 204.0f, 0.0f, NULL, 0 },
    { -269, 100, -50, 0.0f, 0.0f, 0.0f, NULL, 0 },
    { 0, 0, -1000, 0.0f, 1.8e+02f, 0.0f, NULL, 0 },
    { -269, 122, -280, 0.0f, 0.0f, 0.0f, NULL, 0 }
};
s32 pointerAngles[3] = { 133, 157, 180 };
s32 playerViews[3] = { 0, 4, 5 };

/*
=====================
AdjustCameraProc

The C buttons turn the camera for the player whose turn it is.
=====================
*/
struct procResult_s AdjustCameraProc(proc_t *proc) {
    struct procResult_s result;
    s32 unused;  /* NOTE: unused in the original */
    obj_t *cam;

    result.w[1] = 1;
    result.w[0] = 0;
    if (proc->data->adjustCamera.player != curPlayer) {
        return result;
    }
    if ((playerPad.button & 1 & 0xFFFF) != 0) {
        cameraTurn[curPlayer][1] = cameraTurn[curPlayer][1] - 0.5;
    }
    if ((playerPad.button & 2 & 0xFFFF) != 0) {
        cameraTurn[curPlayer][1] = cameraTurn[curPlayer][1] + 0.5;
    }
    if ((playerPad.button & 4 & 0xFFFF) != 0) {
        cameraTurn[curPlayer][0] = cameraTurn[curPlayer][0] - 0.5;
    }
    if ((playerPad.button & 8 & 0xFFFF) != 0) {
        cameraTurn[curPlayer][0] = cameraTurn[curPlayer][0] + 0.5;
    }
    cam = FindObj(0x3000000, 0xFF000000);
    cam->roll = views[1].roll + cameraTurn[curPlayer][0];
    cam->pitch = views[1].pitch + cameraTurn[curPlayer][1];
    return result;
}

/*
=====================
SetGameView

SetView for a step of a turn.
=====================
*/
void SetGameView(s32 view, s32 cpu) {
    obj_t *obj;
    proc_t *task;

    obj = FindObj(0x3000000, 0xFF000000);
    task = FindProc(0x2010000, 0xFFFF0000);
    if (task != 0) {
        KillProc(task, 1);
    }
    switch (view) {
    case 0:
        SetView(obj, playerViews[curPlayer]);
        return;
    case 1:
        task = FindProc(0x2010000, 0xFFFF0000);
        if (task == 0 && cpu == 0) {
            task = CreatProc(AdjustCameraProc, curPlayer | 0x2010000);
            task->data->adjustCamera.player = curPlayer;
        }
        SetView(obj, view);
        return;
    case 3:
        if (round == 2) {
            SetView(obj, 18);
        } else {
            SetView(obj, view);
        }
        return;
    }
    SetView(obj, view);
}

/*
=====================
RoundOverProc

The puzzle is solved: the camera, the movie, then the next round or the end of the game.
=====================
*/
struct procResult_s RoundOverProc(proc_t *proc) {
    struct procResult_s result;
    s32 unused;  /* NOTE: unused in the original */
    obj_t *obj;
    s32 event;

    result.w[1] = 1;
    result.w[0] = 0;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == PRC_EVENT_NULL) {
            break;
        }
        switch (event) {
        case PRC_EVENT_INIT:
            SetGameView(3, 0);
            SetVannaAnim(1);
            PlayContestantAnims();
            if (round != 2) {
                PlayContestantClip(0, PRC_EVENT_NULL, curPlayer);
            }
            result.w[1] = 1;
            result.w[0] = 320 / frameRetraces;
            return result;
        case PRC_EVENT_DONE_CAMPATH:
            SetGameView(3, 0);
            ResetBoard();
            ProcPostEvent(PRC_EVENT_STOP_FLASHING_PUZZLE);
            if (round == 2) {
                PlayMovie(7, PRC_EVENT_START_ROUND, 180, 20);
            } else {
                PlayMovie(6, PRC_EVENT_START_ROUND, 180, 20);
            }
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    SetVannaStill();
    PlayContestantAnims();
    round++;
    if (gameOver == 0 && round < numRounds) {
        SetCameraView(13);
        if (round == 2) {
            shownJackpot = 0;
            jackpot = 5000;
            ShowJackpot();
        }
        obj = FindObj(0x4010000, -1);
        obj->pitch = wheelStartAngles[round] - pointerAngles[1];
        obj->pitch = obj->pitch - 360.0f;
        result.w[1] = 2;
        result.w[0] = PRC_EVENT_DONE_CAMPATH;
        return result;
    } else {
        KillProcClass(0x7010000, -1, 0);
        gameOver = 1;
        round = 6;
        CreatProc(WinnerProc, proc->data->playerProc.player | 0x2000600);
        FindWinner();
        result.w[1] = 0;
        result.w[0] = 0;
        return result;
    }
    return result;
}

/*
=====================
WinnerProc

Shows the winner of the game.
=====================
*/
struct procResult_s WinnerProc(proc_t *proc) {
    struct procResult_s ret;
    s32 unused;   /* NOTE: unused in the original */
    s32 unused2;  /* NOTE: unused in the original */
    s32 event;

    ret.w[1] = 1;
    ret.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != PRC_EVENT_NULL) {
        switch (event) {
        case PRC_EVENT_INIT:
            SetGameView(17, 0);
            PlayContestantAnims();
            HideOtherContestants();
            applause += 3;
            if (players[curPlayer].winSound > 0) {
                PlaySound(players[curPlayer].winSound);
            }
            ret.w[1] = 1;
            ret.w[0] = 45 / frameRetraces;
            return ret;
        }
    }
    if (curPlayer == 0) {
        PlayMovie(11, PRC_EVENT_BONUS_ROUND, 185, 20);
    } else {
        PlayMovieCorner(11, PRC_EVENT_BONUS_ROUND);
    }
    ret.w[1] = 0;
    ret.w[0] = 0;
    return ret;
}

/*
=====================
SpinProc

A person spins: the wheel, the wedge, then a consonant.
=====================
*/
struct procResult_s SpinProc(proc_t *proc) {
    struct procResult_s result;
    proc_t *task;
    obj_t *node;
    s32 event;

    result.w[1] = 1;
    result.w[0] = 0;
    if (proc->data->playerProc.player != curPlayer) {
        ProcClearMessages(proc);
        return result;
    }
    while ((event = ProcGetMessage(proc)) != PRC_EVENT_NULL) {
        switch (event) {
        case PRC_EVENT_INIT:
            SetGameView(0, 0);
            task = CreatProc(WheelPullProc, 0x4000000);
            result.w[1] = 2;
            result.w[0] = PRC_EVENT_PLAYER_SPUN;
            return result;
        case PRC_EVENT_PLAYER_SPUN:
            SetGameView(0, 0);
            task = CreatProc(WheelSpinProc, 0x4030000);
            node = FindObj(0x4010000, 0xFFFF0000);
            task->data->wheelSpin.wheel = node;
            if (wheelSpeed > 50.0f) {
                task->data->wheelSpin.speed = wheelSpeed + guRandom() % 10;
            } else {
                task->data->wheelSpin.speed = (f32)(guRandom() % 10 + 50) + wheelSpeed;
            }
            if (task->data->wheelSpin.speed > 80.0) {
                ProcPostMessage(proc, PRC_EVENT_WHEEL_LONG_SPIN, 0);
                result.w[1] = 1;
                result.w[0] = 40 / frameRetraces;
                return result;
            } else {
                result.w[1] = 2;
                result.w[0] = -1;
                return result;
            }
            break;
        case PRC_EVENT_WHEEL_LONG_SPIN:
            task = FindProc(0x4030000, -1);
            if (task->data->wheelSpin.speed >= 110.0) {
                if (guRandom() % 100 >= 51) {
                    SetGameView(11, 0);
                } else {
                    SetGameView(15, 1);
                }
            } else {
                SetGameView(3, 0);
            }
            result.w[1] = 2;
            result.w[0] = PRC_EVENT_WHEEL_ALMOST_STOPPED;
            break;
        case PRC_EVENT_WHEEL_ALMOST_STOPPED:
            SetGameView(0, 0);
            result.w[1] = 2;
            result.w[0] = PRC_EVENT_WHEEL_STOPPED;
            break;
        case PRC_EVENT_WHEEL_STOPPED:
            node = FindObj(0x4010000, 0xFFFF0000);
            ApplyWedge(0);
            if (GetWedgeValue() == -2 || GetWedgeValue() == -1) {
                SetGameView(0, 0);
                SetContestantsStill();
                StartRumble(players[curPlayer].controller, 30, 0.8f);
                if (MustLoseTurn() != 0) {
                    if (GetWedgeValue() == -2) {
                        PlayMovieCorner(12, PRC_EVENT_VIDEO_DONE);
                        result.w[1] = 2;
                        result.w[0] = PRC_EVENT_VIDEO_DONE;
                        return result;
                    } else {
                        if (PlayContestantClip(1, PRC_EVENT_VIDEO_DONE, curPlayer) != 0) {
                            result.w[1] = 2;
                            result.w[0] = PRC_EVENT_VIDEO_DONE;
                        } else {
                            LoseTurn();
                            ProcPostEvent(PRC_EVENT_DONE_SPINING);
                            result.w[1] = 0;
                        }
                        return result;
                    }
                }
                LoseTurn();
                result.w[1] = 0;
                result.w[0] = 0;
                return result;
            }
            SetGameView(3, 0);
            PlayContestantAnims();
            StartLetterPick();
            result.w[1] = 2;
            result.w[0] = PRC_EVENT_DONE_SELECTING;
            break;
        case PRC_EVENT_VIDEO_DONE:
            LoseTurn();
            ProcPostEvent(PRC_EVENT_DONE_SPINING);
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
            if (CallLetter(curLetter, 0) > 0) {
                ShowLetter(curLetter);
                task = CreatProc(LightLetterProc, 0x1000000);
                task->data->lightLetter.letter = curLetter;
                result.w[1] = 2;
                result.w[0] = PRC_EVENT_DONE_REVEALING;
            } else {
                PlaySound(1);
                StartRumble(players[curPlayer].controller, 30, 0.8f);
                if (LoseTurn() != 0) {
                    ProcPostEvent(PRC_EVENT_DONE_SPINING);
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
BuyVowelProc

A person buys a vowel for 250.
=====================
*/
struct procResult_s BuyVowelProc(proc_t *proc) {
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
                StartRumble(players[curPlayer].controller, 30, 0.8f);
                ret.w[1] = 1;
                ret.w[0] = 30 / frameRetraces;
                return ret;
            } else {
                if (GetUncalledKinds() == 3) {
                    PlayMovieCorner(1, PRC_EVENT_VIDEO_DONE);
                    ret.w[1] = 2;
                    ret.w[0] = PRC_EVENT_VIDEO_DONE;
                    return ret;
                } else {
                    SetGameView(3, 0);
                    StartLetterPick();
                    ret.w[1] = 2;
                    ret.w[0] = PRC_EVENT_DONE_SELECTING;
                }
            }
            break;
        case PRC_EVENT_VIDEO_DONE:
            ProcPostEvent(PRC_EVENT_DONE_VOWEL);
            ret.w[1] = 0;
            ret.w[1] = 0;
            return ret;
        case PRC_EVENT_DONE_SELECTING:
            PlaySound(players[curPlayer].letterSounds + (curLetter - 'A'));
            ProcPostMessage(proc, PRC_EVENT_DONE_SAYING, 0);
            ret.w[1] = 1;
            ret.w[0] = 30 / frameRetraces;
            return ret;
        case PRC_EVENT_DONE_SAYING:
            if (CallLetter(curLetter, 1) > 0) {
                ShowLetter(curLetter);
                task = CreatProc(LightLetterProc, 0x1000000);
                task->data->lightLetter.letter = curLetter;
                ret.w[1] = 2;
                ret.w[0] = PRC_EVENT_DONE_REVEALING;
            } else {
                PlaySound(1);
                StartRumble(players[curPlayer].controller, 30, 0.8f);
                if (LoseTurn() != 0) {
                    ProcPostEvent(PRC_EVENT_DONE_VOWEL);
                }
                ret.w[1] = 0;
                ret.w[0] = 0;
                return ret;
            }
            break;
        case PRC_EVENT_NOT_ENOUGH:
            ProcPostMessage(proc, PRC_EVENT_NOT_ENOUGH2, 0);
            PlaySound(150);
            ret.w[1] = 1;
            ret.w[0] = 60 / frameRetraces;
            return ret;
        case PRC_EVENT_NOT_ENOUGH2:
            ProcPostEvent(PRC_EVENT_DONE_VOWEL);
            LoseTurn();
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        case PRC_EVENT_DONE_REVEALING:
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
SolveProc

A person solves the puzzle.
=====================
*/
struct procResult_s SolveProc(proc_t *proc) {
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
    task = FindProc(0x1020000, -1);
    while ((event = ProcGetMessage(proc)) != PRC_EVENT_NULL) {
        switch (event) {
        case PRC_EVENT_INIT:
            StartSolvePuzzle();
            SetGameView(3, 0);
            ret.w[1] = 2;
            ret.w[0] = PRC_EVENT_DONE_SELECTING;
            return ret;
        case PRC_EVENT_DONE_SELECTING:
            if (CheckSolve() == 1) {
                applause = applause + 2;
                ProcPostMessage(task, PRC_EVENT_HIGHLIGHT_ALL, 0);
                ProcPostEvent(PRC_EVENT_DONE_SOLVE);
                ret.w[1] = 0;
                ret.w[0] = 0;
            } else {
                ProcPostMessage(task, PRC_EVENT_CLEAR_GUESSED, 0);
                PlaySound(1);
                StartRumble(players[curPlayer].controller, 30, 0.8f);
                if (finalSpin == 0) {
                    if (LoseTurn() != 0) {
                        ProcPostEvent(PRC_EVENT_DONE_SOLVE);
                    }
                } else {
                    ProcPostEvent(PRC_EVENT_DONE_SOLVE);
                }
                ret.w[1] = 0;
                ret.w[0] = 0;
                return ret;
            }
            break;
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
FinalSpinTurnProc

A person's turn in the final spin: a letter, then the solve.
=====================
*/
struct procResult_s FinalSpinTurnProc(proc_t *proc) {
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
    task = FindProc(0x5000000, -1);
    while ((event = ProcGetMessage(proc)) != PRC_EVENT_NULL) {
        switch (event) {
        case PRC_EVENT_INIT:
            SetGameView(3, 0);
            StartLetterPick();
            ret.w[1] = 2;
            ret.w[0] = PRC_EVENT_DONE_SELECTING;
            break;
        case PRC_EVENT_DONE_SELECTING:
            PlaySound(players[curPlayer].letterSounds + (curLetter - 'A'));
            ProcPostMessage(proc, PRC_EVENT_DONE_SAYING, 0);
            ret.w[1] = 1;
            ret.w[0] = 30 / frameRetraces;
            return ret;
        case PRC_EVENT_DONE_SAYING:
            if (CallLetter(curLetter, 2) > 0) {
                ShowLetter(curLetter);
                task = CreatProc(LightLetterProc, 0x1000000);
                task->data->lightLetter.letter = curLetter;
                ret.w[1] = 2;
                ret.w[0] = PRC_EVENT_DONE_REVEALING;
            } else {
                PlaySound(1);
                StartRumble(players[curPlayer].controller, 30, 0.8f);
                LoseTurn();
                ProcPostEvent(PRC_EVENT_DONE_SPEEDUP);
                ProcPostMessage(task, PRC_EVENT_DONE_SPEEDUP, 0);
                ret.w[1] = 0;
                ret.w[0] = 0;
                return ret;
            }
            break;
        case PRC_EVENT_DONE_REVEALING:
            SetScorePictures(0);
            StartSolveTimer();
            task = CreatProc(SolveProc, proc->data->playerProc.player | 0x2000300);
            task->data->playerProc.player = proc->data->playerProc.player;
            ret.w[1] = 2;
            ret.w[0] = PRC_EVENT_DONE_SOLVE;
            return ret;
        case PRC_EVENT_DONE_SOLVE:
            if (CheckSolve() != 1) {
                LoseTurn();
            }
            ProcPostEvent(PRC_EVENT_DONE_SPEEDUP);
            ProcPostMessage(task, PRC_EVENT_DONE_SPEEDUP, 0);
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
PlayerTurnProc

The turn of a person: makes the procs of its steps; named after the ROM's "player proc".
=====================
*/
struct procResult_s PlayerTurnProc(proc_t *proc) {
    s32 event;
    struct procResult_s ret;
    proc_t *task;

    ret.w[1] = 1;
    ret.w[0] = 0;
    if (proc->data->playerProc.player != curPlayer) {
        while ((event = ProcGetMessage(proc)) != PRC_EVENT_NULL) {
            switch (event) {
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
            task = FindProc(0x5000000, -1);
            ProcPostMessage(task, PRC_EVENT_COMPUTER_DONE, 0);
            /* fallthrough */
        case PRC_EVENT_DONE_SPINING:
        case PRC_EVENT_DONE_VOWEL:
        case PRC_EVENT_DONE_SOLVE:
        case PRC_EVENT_DONE_SPEEDUP:
            SetGameView(3, 0);
            if (CheckSolved(1) == 1) {
                UnlightPlayers();
                task = FindProc(0x5000000, -1);
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
            ret.w[1] = 2;
            ret.w[0] = -1;
            return ret;
        case PRC_EVENT_INIT:
            ret.w[1] = 2;
            ret.w[0] = PRC_EVENT_START_FIRST_ROUND;
            return ret;
        case PRC_EVENT_START_FIRST_ROUND:
            InitBoard();
            /* fallthrough */
        case PRC_EVENT_NEXT_PLAYER:
        case PRC_EVENT_NEXT_ROUND:
        case PRC_EVENT_DONE_FINAL_SPIN:
            if (finalSpin == 1) {
                task = CreatProc(FinalSpinTurnProc, proc->data->playerProc.player | 0x2000400);
                task->data->playerProc.player = proc->data->playerProc.player;
                ret.w[1] = 2;
                ret.w[0] = PRC_EVENT_DONE_SPEEDUP;
                return ret;
            }
            SetGameView(3, 0);
            ret.w[1] = 2;
            ret.w[0] = -1;
            return ret;
        case PRC_EVENT_SPIN_SELECTED:
            if (guRandom() % 100 < 33) {
                PlaySound(players[curPlayer].spinSound);
            }
            jackpotWon = 0;
            task = CreatProc(SpinProc, proc->data->playerProc.player | 0x2000100);
            task->data->playerProc.player = proc->data->playerProc.player;
            ret.w[1] = 2;
            ret.w[0] = PRC_EVENT_DONE_SPINING;
            return ret;
        case PRC_EVENT_SVOWEL_SELECTED:
            PlaySound(players[curPlayer].buyVowelSound);
            jackpotWon = 0;
            task = CreatProc(BuyVowelProc, proc->data->playerProc.player | 0x2000200);
            task->data->playerProc.player = proc->data->playerProc.player;
            ret.w[1] = 2;
            ret.w[0] = PRC_EVENT_DONE_VOWEL;
            return ret;
        case PRC_EVENT_SOLVE_SELECTED:
            PlaySound(players[curPlayer].solveSound);
            task = CreatProc(SolveProc, proc->data->playerProc.player | 0x2000300);
            task->data->playerProc.player = proc->data->playerProc.player;
            ret.w[1] = 2;
            ret.w[0] = PRC_EVENT_DONE_SOLVE;
            return ret;
        case PRC_EVENT_USE_FREE_SPIN:
            jackpotWon = 0;
            task = FindProc(0x5000000, -1);
            curLetter = '3';
            ProcPostMessage(task, PRC_EVENT_COMPUTER_CHANGED, 1);
            StartFreeSpinTimer();
            ret.w[1] = 2;
            ret.w[0] = -1;
            return ret;
        case PRC_EVENT_FREE_TIMEOUT:
            PlaySound(1);
            SetGameView(0, 0);
            NextTurn();
            StartRumble(players[curPlayer].controller, 30, 0.8f);
            ret.w[1] = 2;
            ret.w[0] = -1;
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
        case PRC_EVENT_BONUS_ROUND:
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
AddPlayer

The turn proc of a person.
=====================
*/
void AddPlayer(s32 player) {
    proc_t *task;
    s32 unused;   /* NOTE: unused in the original */
    s32 unused2;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    task = CreatProc(PlayerTurnProc, player | 0x2020000);
    task->data->playerProc.player = player;
}

/*
=====================
InitPlayers

A turn proc for each contestant, a person's or the machine's.
=====================
*/
void InitPlayers(void) {
    s32 unused;  /* NOTE: unused in the original */
    s32 unused2;  /* NOTE: unused in the original */
    s32 i;

    InitCpuLetters();
    for (i = 0; i < 3; i++) {
        if (gameMode == 3) {
            AddDemoCpu(i);
        } else if (players[i].controller < 4) {
            AddPlayer(i);
        } else {
            AddCpu(i);
        }
        cameraTurn[i][0] = 0;
        cameraTurn[i][1] = 0;
    }
    if (gameMode == 3) {
        SetGameView(17, 0);
        return;
    }
    SetGameView(3, 0);
}
