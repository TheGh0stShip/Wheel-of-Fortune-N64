// unit_80016638.c -- procs and the objects they draw, with their setup
//
// The object's text lies between the 4-byte gaps that end InitStage and CreateCamera; its read-only
// data opens with the RCS run at 0x80000E28. The run could start after InitStage or after
// func_80016638: that it starts at the gap, so that func_80016638 belongs here, rests on the premise that
// from 0x8000BAA8 on every object opens its read-only data with an RCS run.

#include "wof.h"

// The #ident line of the system header this object included: the original assembler put the string into
// the read-only data, which it opens. The header is not in this tree, so its line stands here.
#ident "$Revision: 1.17 $"

s32 func_80016638(void) {
    s32 result;

    switch (curView) {
    case 18:
    case 3:
    case 20:
        result = 1;
        break;
    default:
        result = 0;
    }
    return result;
}

s32 func_800166C0(void) {
    s32 result;

    switch (curView) {
    case 3:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 18:
    case 20:
        result = 0;
        break;
    default:
        result = 1;
    }
    return result;
}

/*
=====================
CameraPathProc

Plays a camera move a frame at a time; event 45 when it ends.
=====================
*/
struct procResult_s CameraPathProc(proc_t *proc) {
    s32 event;
    struct procResult_s result;
    obj_t *sp28;

    sp28 = proc->data->cameraPath.unk_00;
    result.w[1] = 1;
    result.w[0] = 0;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            curCamera = &proc->data->cameraPath.path[proc->data->cameraPath.frame];
            return result;
        }
    }
    proc->data->cameraPath.frame += frameRetraces;
    if (proc->data->cameraPath.frame >= proc->data->cameraPath.count) {
        curCamera = proc->data->cameraPath.path - 1 + proc->data->cameraPath.count;
        ProcPostEvent(45);
        result.w[1] = 0;
        result.w[0] = 0;
        return result;
    }
    curCamera = &proc->data->cameraPath.path[proc->data->cameraPath.frame];
    return result;
}

/*
=====================
SetView

Puts the camera obj at a view, and plays its camera move if it has one.
=====================
*/
void SetView(obj_t *obj, s32 view) {
    proc_t *task;

    curView = view;
    obj->scale = 1.0f;
    obj->x = views[view].x;
    obj->y = views[view].y;
    obj->z = views[view].z;
    obj->roll = views[view].roll;
    obj->pitch = views[view].pitch;
    obj->heading = views[view].heading;
    obj->dl = 0;
    task = FindProc(0x3010000, -1);
    if (task != 0) {
        KillProc(task, 0);
    }
    if (views[view].path != 0) {
        task = CreatProc(CameraPathProc, 0x3010000);
        task->data->cameraPath.path = views[view].path;
        task->data->cameraPath.frame = 0;
        task->data->cameraPath.count = views[view].count;
        cameraUpX = views[view].roll;
        cameraUpY = views[view].pitch;
        cameraUpZ = views[view].heading;
        return;
    }
    curCamera = 0;
    cameraUpX = 0;
    cameraUpY = 0;
    cameraUpZ = 0;
}

/*
=====================
SetCameraView

SetView on the camera obj.
=====================
*/
void SetCameraView(s32 view) {
    obj_t *sp10;

    sp10 = FindObj(0x03000000, 0xFF000000);
    SetView(sp10, view);
}

/*
=====================
CameraProc

The proc of the camera obj, which does nothing.
=====================
*/
struct procResult_s CameraProc(proc_t *proc) {
    struct procResult_s result;
    obj_t *sp20;

    sp20 = proc->data->obj;
    ProcClearMessages(proc);
    result.w[1] = 1;
    result.w[0] = 0;
    return result;
}

/*
=====================
DrawCamera

The draw function of the camera: the projection and guLookAt, from the opening, a move or the obj.
=====================
*/
void DrawCamera(obj_t *obj, frame_t *frame) {
    s32 step;
    u16 perspNorm;
    f32 eye[4][4];
    f32 scale[4][4];
    f32 rot[4][4];
    f32 up[4][4];

    guPerspective(&frame->projection, &perspNorm, 33.0f, 4.0f / 3.0f, 200.0f, 5000.0f, obj->scale);
    gSPPerspNormalize(glistp++, perspNorm);
    if (gameMode == 1) {
        step = openingFrame;
        if (step < 0) {
            step = 0;
        }
        if (openingFrames - 1 < step) {
            step = openingFrames - 1;
        }
        guLookAt(&frame->viewing, openingPath[step].eyeX, openingPath[step].eyeY, openingPath[step].eyeZ, openingPath[step].atX, openingPath[step].atY, openingPath[step].atZ, openingPath[step].upX, openingPath[step].upY, openingPath[step].upZ);
    } else if (curCamera != 0) {
        if (cameraUpX + cameraUpY + cameraUpZ == 0.0f) {
            guLookAt(&frame->viewing, curCamera->eyeX, curCamera->eyeY, curCamera->eyeZ, curCamera->atX, curCamera->atY, curCamera->atZ, 0.0f, 1.0f, 0.0f);
        } else {
            guLookAt(&frame->viewing, curCamera->eyeX, curCamera->eyeY, curCamera->eyeZ, curCamera->atX, curCamera->atY, curCamera->atZ, cameraUpX, cameraUpY, cameraUpZ);
        }
    } else {
        guTranslateF(eye, 0, 0, -1000.0f);
        guScaleF(scale, obj->scale, obj->scale, obj->scale);
        guRotateRPYF(rot, obj->roll, obj->pitch, obj->heading);
        guMtxCatF(eye, scale, eye);
        guMtxCatF(eye, rot, eye);
        guTranslateF(up, 0, 1.0f, 0);
        guScaleF(scale, obj->scale, obj->scale, obj->scale);
        guRotateRPYF(rot, obj->roll, obj->pitch, obj->heading);
        guMtxCatF(up, scale, up);
        guMtxCatF(up, rot, up);
        guLookAt(&frame->viewing, obj->x, obj->y, obj->z, eye[3][0] + obj->x, eye[3][1] + obj->y, eye[3][2] + obj->z, up[3][0], up[3][1], up[3][2]);
    }
    gSPMatrix(glistp++, &frame->projection, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &frame->viewing, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    gSPSetLights6(glistp++, D_8004B7B8);
}

/*
=====================
InitCamera

Makes the camera obj of a proc.
=====================
*/
void InitCamera(proc_t *proc) {
    obj_t *handle;

    handle = CreatObj(proc->id, DrawCamera, 0x3000000);
    if (handle == 0) {
        return;
    }
    proc->data->obj = handle;
    SetView(handle, 1);
}

/*
=====================
CreateCamera

Makes the camera proc and its obj.
=====================
*/
void CreateCamera(void) {
    proc_t *task;
    s32 unused;  /* NOTE: unused in the original */
    s32 unused2;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    curCamera = 0;
    task = CreatProc(CameraProc, 0x3000000);
    if (task == 0) {
        return;
    }
    InitCamera(task);
}
