// AdjustCameraProc.c -- the C buttons turn the camera for the player whose turn it is

#include "wof.h"

/*
=====================
AdjustCameraProc

The C buttons turn the camera for the player whose turn it is.
=====================
*/
struct procResult_s AdjustCameraProc(proc_t *proc) {
    struct procResult_s sp10;
    s32 unused;  /* NOTE: unused in the original */
    obj_t *cam;

    sp10.w[1] = 1;
    sp10.w[0] = 0;
    if (proc->data->adjustCamera.player != curPlayer) {
        return sp10;
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
    return sp10;
}
