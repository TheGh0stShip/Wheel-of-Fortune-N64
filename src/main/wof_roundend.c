// wof_roundend.c -- the camera of a turn, the end of a round and the winner of the game
//
// One object from AdjustCameraProc to WinnerProc: AdjustCameraProc's read-only items run on into
// SetGameView's with no 8-byte boundary between them, and SetGameView and RoundOverProc end off an
// 8-byte boundary with the next function right after. Its data runs from views to playerViews with
// no gap; pointerAngles, between them, is this object's too (wof_stage only uses it). The RCS run
// that opens its read-only data could also open an object starting a few functions before
// AdjustCameraProc; where the object starts and where it ends after WinnerProc the text does not
// say.

#include "wof.h"

// The #ident line of the system header this object included: the original assembler put the string
// into the read-only data, which it opens. The header is not in this tree, so its line stands here.
#ident "$Revision: 1.17 $"

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
    { 0, 0, 0, 0.0f, 0.0f, 0.0f, D_800650B0, 241 },
    { 0, 0, 0, 0.0f, 0.0f, 0.0f, D_80069908, 301 },
    { 0, 0, 0, 0.410065f, 0.241922f, 0.879387f, D_80068C38, 91 },
    { 0, 0, 0, 0.0f, 0.0f, 0.0f, D_80067F68, 91 },
    { 0, 0, 0, 0.0f, 0.0f, 0.0f, D_8005C960, 241 },
    { 0, 0, 0, 0.0f, 0.0f, 0.0f, D_8006C360, 181 },
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
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            SetGameView(3, 0);
            SetVannaAnim(1);
            func_80032B10();
            if (round != 2) {
                PlayContestantClip(0, 0, curPlayer);
            }
            result.w[1] = 1;
            result.w[0] = 320 / frameRetraces;
            return result;
        case 45:
            SetGameView(3, 0);
            ResetBoard();
            ProcPostEvent(47);
            if (round == 2) {
                PlayMovie(7, 39, 180, 20);
            } else {
                PlayMovie(6, 39, 180, 20);
            }
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    func_80032858();
    func_80032B10();
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
        result.w[0] = 45;
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
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            SetGameView(17, 0);
            func_80032B10();
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
        PlayMovie(11, 42, 185, 20);
    } else {
        PlayMovieCorner(11, 42);
    }
    ret.w[1] = 0;
    ret.w[0] = 0;
    return ret;
}
