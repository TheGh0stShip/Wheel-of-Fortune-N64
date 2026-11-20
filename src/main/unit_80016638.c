// unit_80016638.c -- procs and the objects they draw, with their setup
//
// The object's text lies between the 4-byte gaps that end func_80016310 and func_800174DC; its read-only
// data opens with the RCS run at 0x80000E28. The run could start after func_80016310 or after
// func_80016638: that it starts at the gap, so that func_80016638 belongs here, rests on the premise that
// from 0x8000BAA8 on every object opens its read-only data with an RCS run.

#include "wof.h"

// The #ident line of the system header this object included: the original assembler put the string into
// the read-only data, which it opens. The header is not in this tree, so its line stands here.
#ident "$Revision: 1.17 $"

s32 func_80016638(void) {
    s32 result;

    switch (D_800BA2BC) {
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

    switch (D_800BA2BC) {
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

struct procResult_s func_80016734(proc_t *proc) {
    s32 event;
    struct procResult_s result;
    obj_t *sp28;

    sp28 = proc->unk_30->data80016734.unk_00;
    result.w[1] = 1;
    result.w[0] = 0;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            D_800BA5D8 = &proc->unk_30->data80016734.unk_08[proc->unk_30->data80016734.unk_0C];
            return result;
        }
    }
    proc->unk_30->data80016734.unk_0C += frameRetraces;
    if (proc->unk_30->data80016734.unk_0C >= proc->unk_30->data80016734.unk_10) {
        D_800BA5D8 = proc->unk_30->data80016734.unk_08 - 1 + proc->unk_30->data80016734.unk_10;
        ProcPostEvent(45);
        result.w[1] = 0;
        result.w[0] = 0;
        return result;
    }
    D_800BA5D8 = &proc->unk_30->data80016734.unk_08[proc->unk_30->data80016734.unk_0C];
    return result;
}

void func_80016944(obj_t *obj, s32 arg1) {
    proc_t *task;

    D_800BA2BC = arg1;
    obj->scale = 1.0f;
    obj->x = D_80057F50[arg1].x;
    obj->y = D_80057F50[arg1].y;
    obj->z = D_80057F50[arg1].z;
    obj->unk_28 = D_80057F50[arg1].unk_0C;
    obj->unk_2C = D_80057F50[arg1].unk_10;
    obj->unk_30 = D_80057F50[arg1].unk_14;
    obj->unk_48 = 0;
    task = FindProc(0x3010000, -1);
    if (task != 0) {
        KillProc(task, 0);
    }
    if (D_80057F50[arg1].path != 0) {
        task = CreatProc(func_80016734, 0x3010000);
        task->unk_30->data80016734.unk_08 = D_80057F50[arg1].path;
        task->unk_30->data80016734.unk_0C = 0;
        task->unk_30->data80016734.unk_10 = D_80057F50[arg1].count;
        D_800B6BE8 = D_80057F50[arg1].unk_0C;
        D_800B6BEC = D_80057F50[arg1].unk_10;
        D_800B6BF0 = D_80057F50[arg1].unk_14;
        return;
    }
    D_800BA5D8 = 0;
    D_800B6BE8 = 0;
    D_800B6BEC = 0;
    D_800B6BF0 = 0;
}

void func_80016B9C(s32 arg0) {
    obj_t *sp10;

    sp10 = FindObj(0x03000000, 0xFF000000);
    func_80016944(sp10, arg0);
}

struct procResult_s func_80016BEC(proc_t *proc) {
    struct procResult_s result;
    obj_t *sp20;

    sp20 = proc->unk_30->obj;
    ProcClearMessages(proc);
    result.w[1] = 1;
    result.w[0] = 0;
    return result;
}

void func_80016C78(obj_t *obj, frame_t *frame) {
    s32 step;
    u16 perspNorm;
    f32 eye[4][4];
    f32 scale[4][4];
    f32 rot[4][4];
    f32 up[4][4];

    guPerspective(&frame->projection, &perspNorm, 33.0f, 4.0f / 3.0f, 200.0f, 5000.0f, obj->scale);
    gSPPerspNormalize(glistp++, perspNorm);
    if (D_800BCD54 == 1) {
        step = D_800B3994;
        if (step < 0) {
            step = 0;
        }
        if (D_800B6198 - 1 < step) {
            step = D_800B6198 - 1;
        }
        guLookAt(&frame->viewing, D_8005EB48[step].eyeX, D_8005EB48[step].eyeY, D_8005EB48[step].eyeZ, D_8005EB48[step].atX, D_8005EB48[step].atY, D_8005EB48[step].atZ, D_8005EB48[step].upX, D_8005EB48[step].upY, D_8005EB48[step].upZ);
    } else if (D_800BA5D8 != 0) {
        if (D_800B6BE8 + D_800B6BEC + D_800B6BF0 == 0.0f) {
            guLookAt(&frame->viewing, D_800BA5D8->eyeX, D_800BA5D8->eyeY, D_800BA5D8->eyeZ, D_800BA5D8->atX, D_800BA5D8->atY, D_800BA5D8->atZ, 0.0f, 1.0f, 0.0f);
        } else {
            guLookAt(&frame->viewing, D_800BA5D8->eyeX, D_800BA5D8->eyeY, D_800BA5D8->eyeZ, D_800BA5D8->atX, D_800BA5D8->atY, D_800BA5D8->atZ, D_800B6BE8, D_800B6BEC, D_800B6BF0);
        }
    } else {
        guTranslateF(eye, 0, 0, -1000.0f);
        guScaleF(scale, obj->scale, obj->scale, obj->scale);
        guRotateRPYF(rot, obj->unk_28, obj->unk_2C, obj->unk_30);
        guMtxCatF(eye, scale, eye);
        guMtxCatF(eye, rot, eye);
        guTranslateF(up, 0, 1.0f, 0);
        guScaleF(scale, obj->scale, obj->scale, obj->scale);
        guRotateRPYF(rot, obj->unk_28, obj->unk_2C, obj->unk_30);
        guMtxCatF(up, scale, up);
        guMtxCatF(up, rot, up);
        guLookAt(&frame->viewing, obj->x, obj->y, obj->z, eye[3][0] + obj->x, eye[3][1] + obj->y, eye[3][2] + obj->z, up[3][0], up[3][1], up[3][2]);
    }
    gSPMatrix(glistp++, &frame->projection, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &frame->viewing, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    gSPSetLights6(glistp++, D_8004B7B8);
}

void func_8001745C(proc_t *proc) {
    obj_t *handle;

    handle = CreatObj(proc->unk_04, func_80016C78, 0x3000000);
    if (handle == 0) {
        return;
    }
    proc->unk_30->obj = handle;
    func_80016944(handle, 1);
}

void func_800174DC(void) {
    proc_t *task;
    s32 unused;  /* NOTE: unused in the original */
    s32 unused2;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    D_800BA5D8 = 0;
    task = CreatProc(func_80016BEC, 0x3000000);
    if (task == 0) {
        return;
    }
    func_8001745C(task);
}
