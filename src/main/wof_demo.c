// wof_demo.c -- the demo the machine plays
//
// The object's read-only data opens with the RCS run at 0x80000B00, the next object's with the one at
// 0x80000B90: the functions whose data lie between the two are this object's.

#include "wof.h"

// The #ident line of the system header this object included: the original assembler put the string into
// the read-only data, which it opens. The header is not in this tree, so its line stands here.
#ident "$Revision: 1.17 $"

/*
=====================
DemoProc

Plays the demo's movie and, when the demo ends, goes back to the opening or to the title on START.
=====================
*/
struct procResult_s DemoProc(proc_t *proc) {
    struct procResult_s result;
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
            ProcPostMessage(proc, 15, 0);
            applause += 2;
            result.w[0] = 30 / frameRetraces;
            return result;
        case 15:
            PlayMovie(7, 40, 180, 20);
            SetCameraView(3);
            return result;
        case 34:
            StopAllSounds();
            result.w[1] = 1;
            result.w[0] = 2;
            FreeObjClass(0x1000000, 0xFF000000);
            FreeObjClass(0xA000000, 0xFF000000);
            FreeObjClass(0x4000000, 0xFF000000);
            if ((buttonsPressed & 0x1000) != 0) {
                ProcPostMessage(proc, 36, 0);
            } else {
                ProcPostMessage(proc, 35, 0);
            }
            return result;
        case 35:
            KillOtherProcs(proc);
            InitObjs();
            StopMovie();
            PopMemStack(1);
            RestartOpening();
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        case 36:
            KillOtherProcs(proc);
            InitObjs();
            StopMovie();
            StartMenus();
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    return result;
}

/*
=====================
DemoStub

Empty, and nothing calls it; it lies between DemoProc and StartDemo.
=====================
*/
void DemoStub(s32 arg0, s32 arg1) {
}

/*
=====================
StartDemo

Sets gameMode 3 and starts a game the machine plays.
=====================
*/
void StartDemo(void) {
    s32 unused[4];  /* NOTE: unused in the original; guess: its type, the frame shows at most 16 bytes */

    gameMode = 3;
    cpuSkill = 0.65f;
    do {
    } while (pendingGfx != 0 && retraceCount < 100);
    CreateCamera();
    StartDemoTimer();
    NewGame();
    InitStage();
    InitContestants();
    InitPlayers();
    StartStatus();
    CreatProc(DemoProc, 0x9000000);
    MakeObj(0, 0, DrawPressStart, 0x5000000);
    StartApplause();
}
