// wof_pause.c -- pausing: the pause picture and the sounds paused, the pause proc, and starting it
//
// A 4-byte gap ends the text after StartPauseProc. guess: the boundary before PauseGame and the joins
// after PauseGame and PauseProc. The RCS runs at 0x80001A30 and 0x80001A48, which no function uses, open
// the read-only data of the objects that start at two of the positions after HideOtherContestants,
// PauseGame, PauseProc and StartPauseProc (a text gap, which takes the second); the first goes after
// HideOtherContestants because PauseGame, PauseProc and StartPauseProc are the pause (StartPauseProc
// starts PauseProc), and the project's ruling takes the join everywhere else. The run at 0x80001A30 is
// all of the object's read-only data.

#include "wof.h"

// guess: the RCS run at 0x80001A30 opens this object's read-only data, and is all of it. The run
// is the #ident line of the system header the object included; zeros to an 8-byte boundary and the
// next run follow it, and no function uses it. It lies between wof_anim's read-only data and the
// runs at 0x80001A48 and 0x80001A60, so it opens an object that starts after one of
// HideOtherContestants, PauseGame and PauseProc. Of those, this reading takes the first: the pause's
// three functions as one object, the run at 0x80001A48 opening the object at the 4-byte gap after
// StartPauseProc (wof_applause) and the one at 0x80001A60 the confetti's. The bytes are the same for
// each choice.
#ident "$Revision: 1.17 $"

/*
=====================
PauseGame

Pauses: gameMode 6, the sounds paused, the pause picture shown.
=====================
*/
void PauseGame(void) {
    if (movieDone == 0) {
        return;
    }
    ResetMotors();
    pauseStart = (s32)(osGetTime() / osClockRate);
    pausedMode = gameMode;
    gameMode = 6;
    MakeObj(0, 0, DrawPause, 0x5020000);
    PauseSounds();
}

/*
=====================
PauseProc

START pauses and resumes; 30 seconds without a button in a game pause it too.
=====================
*/
struct procResult_s PauseProc(proc_t *proc) {
    struct procResult_s result;
    proc_t *task;
    s32 unused;  /* NOTE: unused in the original */
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
            lastInputTime = (s32)(osGetTime() / osClockRate);
        }
    }
    pausedTime = 0;
    if (gameMode == 2) {
        if (inputCount > 0) {
            lastInputTime = (s32)(osGetTime() / osClockRate);
            inputCount = 0;
        } else {
            if (((osGetTime() / osClockRate) - lastInputTime) > 30) {
                PauseGame();
                return result;
            }
        }
    } else {
        if (gameMode == 8) {
            if (((buttonsPressed & 0xB000) & 0xFFFF) != 0) {
                task = FindProc(0x6060000, -1);
                if (task != 0) {
                    ProcPostMessage(task, PRC_EVENT_GAME_OVER, 1);
                }
            }
            return result;
        }
    }
    if (((buttonsPressed & 0x1000) & 0xFFFF) != 0) {
        if (gameMode != 6) {
            PauseGame();
        } else {
            FreeObjClass(0x5020000, -1);
            gameMode = pausedMode;
            ResumeSounds();
            pausedTime = ((s32)(osGetTime() / osClockRate)) - pauseStart;
            lastInputTime = (s32)(osGetTime() / osClockRate);
        }
    }
    return result;
}

/*
=====================
StartPauseProc

Creates PauseProc.
=====================
*/
void StartPauseProc(void) {
    CreatProc(PauseProc, 0x0B000000);
}
