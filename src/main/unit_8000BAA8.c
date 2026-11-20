// unit_8000BAA8.c -- procs and object draw functions, with their setup
//
// The object's text starts after the 4-byte gap that ends PopMemStack; its read-only data opens with the
// RCS run at 0x80000AC0, and the next object's with the one at 0x80000B00, which only the position after
// StartOpening can take. That the run at 0x80000AC0 starts at the text gap, and that no object without a
// run hides between the gap and StartOpening, rests on the premise that from 0x8000BAA8 on every object
// opens its read-only data with an RCS run.

#include "wof.h"

// The #ident line of the system header this object included: the original assembler put the string into
// the read-only data, which it opens. The header is not in this tree, so its line stands here.
#ident "$Revision: 1.17 $"

// the one message slot of siLockQ
static OSMesg siLockMsg;

void InitSiLock(void) {
    siLockMade = 1;
    osCreateMesgQueue(&siLockQ, &siLockMsg, 1);
    osSendMesg(&siLockQ, 0, 0);
}

void LockSi(void) {
    OSMesg sp10;

    if (siLockMade == 0) {
        InitSiLock();
    }
    osRecvMesg(&siLockQ, &sp10, 1);
}

void UnlockSi(void) {
    osSendMesg(&siLockQ, 0, 0);
}

void func_8000BBA8(void) {
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    do {
    } while (pendingGfx != 0 && retraceCount < 100);
    gameMode = 2;
    func_800339E8();
    CreateCamera();
    StartRoundTimer();
    NewGame();
    InitStage();
    func_80032BF0();
    InitPlayers();
    StartStatus();
    func_80033CBC();
}

struct procResult_s func_8000BC64(proc_t *proc) {
    struct procResult_s result;
    obj_t *sp20;
    s32 event;

    sp20 = proc->data->obj;
    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            StopAllSounds();
            ProcPostMessage(proc, 36, 0);
            result.w[1] = 1;
            result.w[0] = 2;
            return result;
        case 36:
            KillOtherProcs(proc);
            InitObjs();
            PopMemStack(1);
            func_8000BBA8();
            SetCameraView(12);
            result.w[1] = 2;
            result.w[0] = 45;
            return result;
        case 45:
            SetCameraView(3);
            func_800219B8(5, 40, 180, 20);
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
    }
    return result;
}

void func_8000BE6C(void) {
    CreatProc(func_8000BC64, 0);
}

struct procResult_s func_8000BEA8(proc_t *proc) {
    f32 mtx[4][4];
    f32 rot[4][4];
    struct procResult_s result;
    obj_t *obj;
    s32 event;

    obj = proc->data->data8000BEA8.unk_00;
    result.w[1] = 1;
    result.w[0] = 0;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            result.w[1] = 1;
            result.w[0] = 2;
            return result;
        case 36:
            KillOtherProcs(proc);
            InitObjs();
            PopMemStack(1);
            func_80026EB4();
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        case 34:
            KillOtherProcs(proc);
            InitObjs();
            PopMemStack(1);
            StartDemo();
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
    }
    if ((buttonsPressed & 0x1000) != 0) {
        StopAllSounds();
        ProcPostMessage(proc, 36, 0);
        result.w[1] = 1;
        result.w[0] = 2;
        return result;
    }
    if (IsSoundStopped(proc->data->data8000BEA8.unk_04) != 0 || openingFrame >= 720) {
        KillOtherProcs(proc);
        InitObjs();
        PopMemStack(1);
        StartDemo();
        result.w[1] = 0;
        result.w[0] = 1;
        return result;
    }
    result.w[1] = 1;
    result.w[0] = 0;
    if (openingFrame >= 269 && openingFrame < 318) {
        D_800BEE24 = D_800BEE24 + frameRetraces * 5;
    }
    D_800B61AC = D_800B61AC - frameRetraces;
    openingFrame = openingFrame + frameRetraces;
    guTranslateF(mtx, 0, D_800BEE24, 0);
    guRotateRPYF(rot, obj->roll, obj->pitch, obj->heading);
    guMtxCatF(mtx, rot, mtx);
    obj->x = proc->data->data8000BEA8.unk_0C + mtx[3][0];
    obj->y = proc->data->data8000BEA8.unk_10 + mtx[3][1];
    obj->z = proc->data->data8000BEA8.unk_14 + mtx[3][2];
    if (openingFrame >= 721) {
        openingFrame = 720;
    }
    return result;
}

struct procResult_s func_8000C310(proc_t *proc) {
    struct procResult_s result;
    obj_t *obj;
    s32 event;

    obj = proc->data->data8000C310.unk_00;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 34:
        case 36:
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
    }
    result.w[1] = 1;
    result.w[0] = 0;
    ProcClearMessages(proc);
    result.w[1] = 1;
    result.w[0] = 0;
    obj->pitch -= (f32)frameRetraces;
    if (openingFrame >= 601) {
        obj->y = obj->y + frameRetraces;
    }
    if (obj->y >= 41) {
        obj->y = 40;
    }
    if (openingFrame % 2 == 1) {
        if (obj->dl == D_011358C0) {
            obj->dl = D_01135908;
        } else {
            obj->dl = D_011358C0;
        }
    }
    return result;
}

struct procResult_s func_8000C50C(proc_t *proc) {
    f32 mtxA[4][4];
    f32 mtxB[4][4];
    struct procResult_s result;
    obj_t *pos;
    s32 event;
    s32 unused;  /* NOTE: unused in the original; func_8000C6C4 keeps an index here */

    pos = proc->data->data8000C50C.unk_00;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 34:
        case 36:
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
    }
    guTranslateF(mtxA, 0, 0, D_800BEE24);
    guRotateRPYF(mtxB, 0, proc->data->data8000C50C.unk_08 * 15, 0);
    guMtxCatF(mtxA, mtxB, mtxA);
    pos->x = mtxA[3][0];
    pos->y = mtxA[3][1];
    pos->z = mtxA[3][2];
    result.w[1] = 1;
    result.w[0] = 0;
    return result;
}

struct procResult_s func_8000C6C4(proc_t *proc) {
    f32 mtx[4][4];
    f32 rot[4][4];
    struct procResult_s ret;
    obj_t *pos;
    s32 event;
    s32 index;

    pos = proc->data->data8000C6C4.pos;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 34:
        case 36:
            ret.w[1] = 0;
            ret.w[0] = 1;
            return ret;
        }
    }
    index = proc->data->data8000C6C4.unk_08;
    guTranslateF(mtx, (f32)D_800BEE24 * D_80057808[index].unk_08, (f32)D_800BEE24, 0);
    guRotateRPYF(rot, -61.317f, 58.385f, -9.848f);
    guMtxCatF(mtx, rot, mtx);
    pos->x = (s32)mtx[3][0];
    pos->y = (s32)mtx[3][1];
    pos->z = (s32)mtx[3][2];
    ret.w[1] = 1;
    ret.w[0] = 0;
    return ret;
}

struct procResult_s func_8000C8A8(proc_t *proc) {
    struct procResult_s ret;
    obj_t *cam;
    s32 event;

    cam = proc->data->data8000C8A8.cam;
    ret.w[1] = 1;
    ret.w[0] = 0;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            cam->y = -140;
            cam->z = -380;
        }
    }
    ret.w[1] = 1;
    ret.w[0] = 0;
    if (buttonsPressed & 0x8000) {
        round++;
        if (round >= 4) {
            round = 0;
        }
    }
    if (buttonsPressed & 0x4000) {
        round--;
        if (round < 0) {
            round = 3;
        }
    }
    if (playerPad.button & 0x10) {
        cam->heading = cam->heading - 0.5;
    }
    if (playerPad.button & 0x20) {
        cam->heading = cam->heading + 0.5;
    }
    if (playerPad.button & 0x200) {
        cam->z = (u16)cam->z + 10;
    }
    if (playerPad.button & 0x100) {
        cam->z = (u16)cam->z - 10;
    }
    if (playerPad.button & 0x800) {
        cam->y = (u16)cam->y + 10;
    }
    if (playerPad.button & 0x400) {
        cam->y = (u16)cam->y - 10;
    }
    return ret;
}

void func_8000CB58(obj_t *obj, frame_t *frame) {
    s32 unused;  /* NOTE: unused in the original */

    if (openingFrame >= 318) {
        guTranslate(&frame->translate[obj->index], (f32)obj->x, (f32)obj->y, (f32)obj->z);
        guScale(&frame->scale[obj->index], obj->scale, obj->scale, obj->scale);
        guRotateRPY(&frame->rotate[obj->index], obj->roll, obj->pitch, obj->heading);
        gSPMatrix(glistp++, &frame->translate[obj->index], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gSPMatrix(glistp++, &frame->scale[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPMatrix(glistp++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPDisplayList(glistp++, &D_010219C8);
        gSPLightColor(glistp++, LIGHT_1, 0x111111FF);
        gSPLightColor(glistp++, LIGHT_2, 0);
        gSPLightColor(glistp++, LIGHT_3, 0x888888FF);
        gSPLightColor(glistp++, LIGHT_4, 0x222222FF);
        gSPLightColor(glistp++, LIGHT_5, 0x222222FF);
        gSPDisplayList(glistp++, &D_0116C028);
        gSPDisplayList(glistp++, &D_01166BF8);
    }
    if (openingFrame < 318) {
        gSPMatrix(glistp++, &D_01176D08, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        guTranslate(&frame->translate[obj->index], (f32)(obj->x + 30), (f32)(obj->y - 50), (f32)(obj->z + 60));
        gSPMatrix(glistp++, &frame->translate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPDisplayList(glistp++, &D_010219C8);
        gSPLightColor(glistp++, LIGHT_1, 0);
        gSPLightColor(glistp++, LIGHT_2, 0);
        gSPLightColor(glistp++, LIGHT_3, 0);
        gSPLightColor(glistp++, LIGHT_4, 0x3C3C3CFF);
        gSPLightColor(glistp++, LIGHT_5, 0x3C3C3CFF);
        gSPDisplayList(glistp++, &D_011696A0);
        gSPLightColor(glistp++, LIGHT_1, 0xC8C8C8FF);
    }
}

void func_8000D400(obj_t *obj, frame_t *frame) {
    if (openingFrame >= 318) {
        return;
    }
    guTranslate(&frame->translate[obj->index], obj->x, obj->y, obj->z);
    guScale(&frame->scale[obj->index], obj->scale, obj->scale, obj->scale);
    guRotateRPY(&frame->rotate[obj->index], obj->roll, obj->pitch, obj->heading);
    guRotateRPY(&frame->unk_04C80, 0, D_800B61AC, 0);
    gSPMatrix(glistp++, &frame->translate[obj->index], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &frame->scale[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &frame->unk_04C80, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPDisplayList(glistp++, D_010219C8);
    gSPDisplayList(glistp++, obj->dl);
}

void func_8000D6D8(obj_t *obj, frame_t *frame) {
    if (openingFrame >= 318) {
        return;
    }
    guTranslate(&frame->rotate[obj->index], obj->x, obj->y, obj->z);
    if (obj->mtx != 0) {
        gSPMatrix(glistp++, obj->mtx, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    }
    gSPMatrix(glistp++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPDisplayList(glistp++, obj->dl);
    gSPPopMatrix(glistp++, G_MTX_MODELVIEW);
    if (obj->mtx != 0) {
        gSPPopMatrix(glistp++, G_MTX_MODELVIEW);
    }
}

void func_8000D8B8(obj_t *obj, frame_t *frame) {
    s32 i;

    if (openingFrame < 318) {
        return;
    }
    guTranslate(&frame->translate[obj->index], (f32)obj->x, (f32)obj->y, (f32)obj->z);
    guScale(&frame->scale[obj->index], obj->scale, obj->scale, obj->scale);
    guRotateRPY(&frame->rotate[obj->index], obj->roll, obj->pitch, obj->heading);
    gSPMatrix(glistp++, &frame->translate[obj->index], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &frame->scale[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPDisplayList(glistp++, D_010219C8);
    gSPDisplayList(glistp++, D_010FA038);
    gSPLightColor(glistp++, LIGHT_1, 0xC8C8C8FF);
    for (i = 0; i < 24; i++) {
        gSPDisplayList(glistp++, D_80057F08[0][i].unk_00);
    }
    gSPMatrix(glistp++, &frame->translate[obj->index], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPDisplayList(glistp++, obj->dl);
}

void func_8000DCA0(obj_t *obj, frame_t *frame) {
    if (openingFrame < 318) {
        return;
    }
    obj->pitch += (f32)(frameRetraces * 2);
    guRotateRPY(&frame->rotate[obj->index], obj->roll,
                  obj->pitch, obj->heading);
    gSPMatrix(glistp++, &D_01176C88, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPDisplayList(glistp++, D_01166928);
    gSPMatrix(glistp++, &D_01176CC8, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPDisplayList(glistp++, D_01166598);
    gDPPipeSync(glistp++);
    gDPSetRenderMode(glistp++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
}

void func_8000DF2C(obj_t *obj, frame_t *frame) {
    s32 unused[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 row;
    s32 col;

    gSPDisplayList(glistp++, &D_01021970);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    gDPSetTextureLUT(glistp++, G_TT_RGBA16);
    gDPLoadTLUT_pal16(glistp++, 0, &D_01146E68);
    gDPPipeSync(glistp++);
    for (row = 0; row < 2; row++) {
        for (col = 0; col < 3; col++) {
            gDPLoadTextureBlock_4b(glistp++, D_80057970[row][col], G_IM_FMT_CI, 64, 64, 0,
                                   G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP,
                                   G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gDPPipeSync(glistp++);
            gSPTextureRectangle(glistp++,
                                (obj->x + col * 64) << 2, (obj->y + row * 64) << 2,
                                (obj->x + col * 64 + 63) << 2, (obj->y + row * 64 + 63) << 2,
                                G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10);
            gDPPipeSync(glistp++);
        }
    }
}

struct procResult_s LogoProc(proc_t *proc) {
    struct procResult_s result;
    obj_t *sp20;
    s32 event;

    sp20 = proc->data->obj;
    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            result.w[1] = 1;
            result.w[0] = 180 / frameRetraces;
            return result;
        case 16:
            KillOtherProcs(proc);
            InitObjs();
            StartOpening();
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    FreeObj(sp20);
    sp20 = MakeObj(0, 0, func_8000DF2C, 0x5020000);
    sp20->x = 64;
    sp20->y = 110;
    proc->data->obj = sp20;
    func_800219B8(23, 16, 104, 20);
    result.w[1] = 2;
    result.w[0] = 16;
    return result;
}

void StartLogos(void) {
    proc_t *task;
    obj_t *sp14;

    gameMode = 1;
    func_80005700();
    sp14 = MakeObj(0, 0, func_800288CC, 0x5030000);
    task = CreatProc(LogoProc, 0x8010000);
    task->data->obj = sp14;
}

void func_8000E738(void) {
    s32 unused;  /* NOTE: unused in the original */
    obj_t *result;

    gameMode = 1;
    func_80005700();
    result = MakeObj(0, 0, func_800289F4, 0x5030000);
}

void RestartOpening(void) {
    func_80005700();
    StartOpening();
    func_8002EDC0();
}

void StartOpening(void) {
    proc_t *task;
    obj_t *obj;
    s32 unused;  /* NOTE: unused in the original */
    s32 i;

    curPlayer = 0;
    gameMode = 1;
    CreateCamera();
    SetCameraView(6);
    openingFrame = 0;
    MakeObj(0, 0, func_8000CB58, 0x8000000);
    MakeObj(0, 0, func_8000DCA0, 0x8000000);
    for (i = 0; i < 14; i++) {
        task = CreatProc(func_8000C6C4, 0x8010000);
        task->data->data8000C6C4.unk_08 = i;
        obj = MakeObj(task, D_80057808[i].unk_00, func_8000D6D8, 0x8010000);
        obj->mtx = D_80057808[i].unk_04;
    }
    task = CreatProc(func_8000C310, 0x8010000);
    obj = MakeObj(task, D_011356C0, func_8000D8B8, 0x8010000);
    obj->y = -20;
    task = CreatProc(func_8000BEA8, 0x8000000);
    obj = MakeObj(task, D_01197D78, func_8000D400, 0x8010000);
    task->data->data8000BEA8.unk_0C = -272.0f;
    task->data->data8000BEA8.unk_10 = 306.0f;
    task->data->data8000BEA8.unk_14 = -411.0f;
    obj->x = -272;
    obj->y = 306;
    obj->z = -411;
    obj->roll = -61.317f;
    obj->pitch = 58.385f;
    obj->heading = -9.848f;
    D_800B61AC = 0;
    task->data->data8000BEA8.unk_04 = PlaySound(15);
    for (i = 0; i < 24; i++) {
        task = CreatProc(func_8000C50C, 0x8010000);
        task->data->data8000C50C.unk_08 = i;
        obj = MakeObj(task, D_800578B0[i], func_8000D6D8, 0x8010000);
        obj->mtx = D_80057910[i];
    }
    MakeObj(0, 0, func_800287A4, 0x5000000);
    openingFrames = 721;
    D_800BEE24 = 0;
}
