// wof_opening.c -- the SI lock, the start of a game, the logos and the opening
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

titleLetter_t titleLetters[14] = {
    { (Gfx *)0x011692C8, (Mtx *)0x01177348, -1.0f },
    { (Gfx *)0x01169090, (Mtx *)0x01177388, 1.0f },
    { (Gfx *)0x01168D10, (Mtx *)0x011773C8, -0.666f },
    { (Gfx *)0x01168890, (Mtx *)0x01177408, 0.666f },
    { (Gfx *)0x01168500, (Mtx *)0x01177448, 0.333f },
    { (Gfx *)0x01168380, (Mtx *)0x01177488, 0.0f },
    { (Gfx *)0x01168130, (Mtx *)0x011774C8, -0.333f },
    { (Gfx *)0x01167EE8, (Mtx *)0x01177508, 1.0f },
    { (Gfx *)0x01167DD0, (Mtx *)0x01177548, -0.666f },
    { (Gfx *)0x01167990, (Mtx *)0x01177588, 0.666f },
    { (Gfx *)0x011676A0, (Mtx *)0x011775C8, -1.333f },
    { (Gfx *)0x01167338, (Mtx *)0x01177608, 0.333f },
    { (Gfx *)0x01166FF0, (Mtx *)0x01177648, -0.333f },
    { (Gfx *)0x01166C28, (Mtx *)0x01177688, -1.0f }
};
Gfx *openingWedgeDls[24] = {
    (Gfx *)0x01196CA0, (Gfx *)0x01196DF8, (Gfx *)0x01196F48, (Gfx *)0x011970B8, (Gfx *)0x01197210,
    (Gfx *)0x01197368, (Gfx *)0x011974B8, (Gfx *)0x01197610, (Gfx *)0x01197768, (Gfx *)0x011978B8,
    (Gfx *)0x01197A08, (Gfx *)0x01197B58, (Gfx *)0x01195AE8, (Gfx *)0x01195C38, (Gfx *)0x01195E18,
    (Gfx *)0x01195F68, (Gfx *)0x011960C0, (Gfx *)0x01196360, (Gfx *)0x01196370, (Gfx *)0x011964C8,
    (Gfx *)0x01196618, (Gfx *)0x01196770, (Gfx *)0x01196AE8, (Gfx *)0x01196AF8
};
Mtx *openingWedgeMtxs[24] = {
    (Mtx *)0x0119AE00, (Mtx *)0x0119ADC0, (Mtx *)0x0119AD80, (Mtx *)0x0119AD40, (Mtx *)0x0119AD00,
    (Mtx *)0x0119ACC0, (Mtx *)0x0119AC80, (Mtx *)0x0119AC40, (Mtx *)0x0119AC00, (Mtx *)0x0119ABC0,
    (Mtx *)0x0119AB80, (Mtx *)0x0119AB40, (Mtx *)0x0119B0C0, (Mtx *)0x0119B080, (Mtx *)0x0119B040,
    (Mtx *)0x0119B000, (Mtx *)0x0119AFC0, (Mtx *)0x0119AF80, (Mtx *)0x0119AF40, (Mtx *)0x0119AF00,
    (Mtx *)0x0119AEC0, NULL, (Mtx *)0x0119AE80, (Mtx *)0x0119AE40
};
s32 logoTiles[2][3] = {
    { 0x01146E88, 0x01147688, 0x01147E88 },
    { 0x01148688, 0x01148E88, 0x01149688 }
};

// the one message slot of siLockQ
static OSMesg siLockMsg;

/*
=====================
InitSiLock

Makes the one-message queue that LockSi and UnlockSi pass between the controller reads and the
rumble pak.
=====================
*/
void InitSiLock(void) {
    siLockMade = 1;
    osCreateMesgQueue(&siLockQ, &siLockMsg, 1);
    osSendMesg(&siLockQ, 0, 0);
}

/*
=====================
LockSi

Takes the SI lock, making it first if need be.
=====================
*/
void LockSi(void) {
    OSMesg msg;

    if (siLockMade == 0) {
        InitSiLock();
    }
    osRecvMesg(&siLockQ, &msg, 1);
}

/*
=====================
UnlockSi

Gives the SI lock back.
=====================
*/
void UnlockSi(void) {
    osSendMesg(&siLockQ, 0, 0);
}

/*
=====================
StartGame

Waits for the graphics, sets gameMode 2 and makes the procs and objs of a game.
=====================
*/
void StartGame(void) {
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    do {
    } while (pendingGfx != 0 && retraceCount < 100);
    gameMode = 2;
    StartPauseProc();
    CreateCamera();
    StartRoundTimer();
    NewGame();
    InitStage();
    InitContestants();
    InitPlayers();
    StartStatus();
    StartApplause();
}

/*
=====================
GameStartProc

Clears the menus, StartGame, then the camera and the movie that open a game.
=====================
*/
struct procResult_s GameStartProc(proc_t *proc) {
    struct procResult_s result;
    obj_t *obj;
    s32 event;

    obj = proc->data->obj;
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
            StartGame();
            SetCameraView(12);
            result.w[1] = 2;
            result.w[0] = 45;
            return result;
        case 45:
            SetCameraView(3);
            PlayMovie(5, 40, 180, 20);
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
    }
    return result;
}

/*
=====================
BeginGame

Creates GameStartProc, when the main menu starts a game.
=====================
*/
void BeginGame(void) {
    CreatProc(GameStartProc, 0);
}

/*
=====================
OpeningProc

Runs the opening: on START the menus, at its end the demo.
=====================
*/
struct procResult_s OpeningProc(proc_t *proc) {
    f32 mtx[4][4];
    f32 rot[4][4];
    struct procResult_s result;
    obj_t *obj;
    s32 event;

    obj = proc->data->opening.obj;
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
            StartMenus();
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
    if (IsSoundStopped(proc->data->opening.music) != 0 || openingFrame >= 720) {
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
        logoSpread = logoSpread + frameRetraces * 5;
    }
    hubAngle = hubAngle - frameRetraces;
    openingFrame = openingFrame + frameRetraces;
    guTranslateF(mtx, 0, logoSpread, 0);
    guRotateRPYF(rot, obj->roll, obj->pitch, obj->heading);
    guMtxCatF(mtx, rot, mtx);
    obj->x = proc->data->opening.x + mtx[3][0];
    obj->y = proc->data->opening.y + mtx[3][1];
    obj->z = proc->data->opening.z + mtx[3][2];
    if (openingFrame >= 721) {
        openingFrame = 720;
    }
    return result;
}

/*
=====================
OpeningWheelProc

Turns the wheel in the opening and flashes its lights; it rises after frame 600.
=====================
*/
struct procResult_s OpeningWheelProc(proc_t *proc) {
    struct procResult_s result;
    obj_t *obj;
    s32 event;

    obj = proc->data->openingWheel.obj;
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
        if (obj->dl == wheelLightsOnDl) {
            obj->dl = wheelLightsOn2Dl;
        } else {
            obj->dl = wheelLightsOnDl;
        }
    }
    return result;
}

/*
=====================
OpeningWedgeProc

Places one of the 24 wedges of the opening around the wheel as the lift rises.
=====================
*/
struct procResult_s OpeningWedgeProc(proc_t *proc) {
    f32 mtxA[4][4];
    f32 mtxB[4][4];
    struct procResult_s result;
    obj_t *pos;
    s32 event;
    s32 unused;  /* NOTE: unused in the original; TitleLetterProc keeps an index here */

    pos = proc->data->openingWedge.obj;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 34:
        case 36:
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
    }
    guTranslateF(mtxA, 0, 0, logoSpread);
    guRotateRPYF(mtxB, 0, proc->data->openingWedge.index * 15, 0);
    guMtxCatF(mtxA, mtxB, mtxA);
    pos->x = mtxA[3][0];
    pos->y = mtxA[3][1];
    pos->z = mtxA[3][2];
    result.w[1] = 1;
    result.w[0] = 0;
    return result;
}

/*
=====================
TitleLetterProc

Places one of the letters of WHEEL OF FORTUNE as the lift rises.
=====================
*/
struct procResult_s TitleLetterProc(proc_t *proc) {
    f32 mtx[4][4];
    f32 rot[4][4];
    struct procResult_s ret;
    obj_t *pos;
    s32 event;
    s32 index;

    pos = proc->data->titleLetterProc.pos;
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
    index = proc->data->titleLetterProc.index;
    guTranslateF(mtx, (f32)logoSpread * titleLetters[index].spread, (f32)logoSpread, 0);
    guRotateRPYF(rot, -61.317f, 58.385f, -9.848f);
    guMtxCatF(mtx, rot, mtx);
    pos->x = (s32)mtx[3][0];
    pos->y = (s32)mtx[3][1];
    pos->z = (s32)mtx[3][2];
    ret.w[1] = 1;
    ret.w[0] = 0;
    return ret;
}

/*
=====================
DebugCameraProc

Moves the camera and changes the round with the buttons; nothing creates it.
=====================
*/
struct procResult_s DebugCameraProc(proc_t *proc) {
    struct procResult_s ret;
    obj_t *cam;
    s32 event;

    cam = proc->data->debugCamera.cam;
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

/*
=====================
DrawOpeningStudio

The draw function of the studio in the opening: from frame 318 the set with its plants and lamps,
before it the blue panels behind the flying logo.
=====================
*/
void DrawOpeningStudio(obj_t *obj, frame_t *frame) {
    s32 unused;  /* NOTE: unused in the original */

    if (openingFrame >= 318) {
        guTranslate(&frame->translate[obj->index], (f32)obj->x, (f32)obj->y, (f32)obj->z);
        guScale(&frame->scale[obj->index], obj->scale, obj->scale, obj->scale);
        guRotateRPY(&frame->rotate[obj->index], obj->roll, obj->pitch, obj->heading);
        gSPMatrix(glistp++, &frame->translate[obj->index], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gSPMatrix(glistp++, &frame->scale[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPMatrix(glistp++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPDisplayList(glistp++, &litSetupDl);
        gSPLightColor(glistp++, LIGHT_1, 0x111111FF);
        gSPLightColor(glistp++, LIGHT_2, 0);
        gSPLightColor(glistp++, LIGHT_3, 0x888888FF);
        gSPLightColor(glistp++, LIGHT_4, 0x222222FF);
        gSPLightColor(glistp++, LIGHT_5, 0x222222FF);
        gSPDisplayList(glistp++, &openingStudioDl);
        gSPDisplayList(glistp++, &openingPropsDl);
    }
    if (openingFrame < 318) {
        gSPMatrix(glistp++, &openingPanelsMtx, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        guTranslate(&frame->translate[obj->index], (f32)(obj->x + 30), (f32)(obj->y - 50), (f32)(obj->z + 60));
        gSPMatrix(glistp++, &frame->translate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPDisplayList(glistp++, &litSetupDl);
        gSPLightColor(glistp++, LIGHT_1, 0);
        gSPLightColor(glistp++, LIGHT_2, 0);
        gSPLightColor(glistp++, LIGHT_3, 0);
        gSPLightColor(glistp++, LIGHT_4, 0x3C3C3CFF);
        gSPLightColor(glistp++, LIGHT_5, 0x3C3C3CFF);
        gSPDisplayList(glistp++, &openingPanelsDl);
        gSPLightColor(glistp++, LIGHT_1, 0xC8C8C8FF);
    }
}

/*
=====================
DrawOpeningHub

The draw function of the hub of the opening's logo, turned by hubAngle, before frame 318.
=====================
*/
void DrawOpeningHub(obj_t *obj, frame_t *frame) {
    if (openingFrame >= 318) {
        return;
    }
    guTranslate(&frame->translate[obj->index], obj->x, obj->y, obj->z);
    guScale(&frame->scale[obj->index], obj->scale, obj->scale, obj->scale);
    guRotateRPY(&frame->rotate[obj->index], obj->roll, obj->pitch, obj->heading);
    guRotateRPY(&frame->hubRotate, 0, hubAngle, 0);
    gSPMatrix(glistp++, &frame->translate[obj->index], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &frame->scale[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &frame->hubRotate, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPDisplayList(glistp++, litSetupDl);
    gSPDisplayList(glistp++, obj->dl);
}

/*
=====================
DrawOpeningPiece

The draw function of a wedge or a title letter in the opening, before frame 318.
=====================
*/
void DrawOpeningPiece(obj_t *obj, frame_t *frame) {
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

/*
=====================
DrawOpeningWheel

The draw function of the wheel in the opening, with its 24 wedges.
=====================
*/
void DrawOpeningWheel(obj_t *obj, frame_t *frame) {
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
    gSPDisplayList(glistp++, litSetupDl);
    gSPDisplayList(glistp++, wheelHubDl);
    gSPLightColor(glistp++, LIGHT_1, 0xC8C8C8FF);
    for (i = 0; i < 24; i++) {
        gSPDisplayList(glistp++, wedgeDls[0][i].dl);
    }
    gSPMatrix(glistp++, &frame->translate[obj->index], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPDisplayList(glistp++, obj->dl);
}

/*
=====================
DrawSearchlights

The draw function of the two searchlight beams of the opening from frame 318, which turn a little
each frame.
=====================
*/
void DrawSearchlights(obj_t *obj, frame_t *frame) {
    if (openingFrame < 318) {
        return;
    }
    obj->pitch += (f32)(frameRetraces * 2);
    guRotateRPY(&frame->rotate[obj->index], obj->roll,
                  obj->pitch, obj->heading);
    gSPMatrix(glistp++, &searchlight1Mtx, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPDisplayList(glistp++, searchlight1Dl);
    gSPMatrix(glistp++, &searchlight2Mtx, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPDisplayList(glistp++, searchlight2Dl);
    gDPPipeSync(glistp++);
    gDPSetRenderMode(glistp++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
}

/*
=====================
DrawLogo

The draw function of the picture LogoProc shows, in six tiles of 64 by 64.
=====================
*/
void DrawLogo(obj_t *obj, frame_t *frame) {
    s32 unused[2];  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */
    s32 row;
    s32 col;

    gSPDisplayList(glistp++, &imageSetupDl);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    gDPSetTextureLUT(glistp++, G_TT_RGBA16);
    gDPLoadTLUT_pal16(glistp++, 0, &logoPalette);
    gDPPipeSync(glistp++);
    for (row = 0; row < 2; row++) {
        for (col = 0; col < 3; col++) {
            gDPLoadTextureBlock_4b(glistp++, logoTiles[row][col], G_IM_FMT_CI, 64, 64, 0,
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

/*
=====================
LogoProc

Shows the pictures before the opening for 3 seconds, then a movie, then StartOpening.
=====================
*/
struct procResult_s LogoProc(proc_t *proc) {
    struct procResult_s result;
    obj_t *obj;
    s32 event;

    obj = proc->data->obj;
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
    FreeObj(obj);
    obj = MakeObj(0, 0, DrawLogo, 0x5020000);
    obj->x = 64;
    obj->y = 110;
    proc->data->obj = obj;
    PlayMovie(23, 16, 104, 20);
    result.w[1] = 2;
    result.w[0] = 16;
    return result;
}

/*
=====================
StartLogos

Starts LogoProc; InitGame's choice when a controller is in.
=====================
*/
void StartLogos(void) {
    proc_t *task;
    obj_t *obj;

    gameMode = 1;
    LoadSceneData();
    obj = MakeObj(0, 0, DrawBootScreen, 0x5030000);
    task = CreatProc(LogoProc, 0x8010000);
    task->data->obj = obj;
}

/*
=====================
ShowNoController

InitGame's choice when no controller is in: a screen and nothing more.
=====================
*/
void ShowNoController(void) {
    s32 unused;  /* NOTE: unused in the original */
    obj_t *result;

    gameMode = 1;
    LoadSceneData();
    result = MakeObj(0, 0, DrawNoController, 0x5030000);
}

/*
=====================
RestartOpening

Starts the opening again after the demo.
=====================
*/
void RestartOpening(void) {
    LoadSceneData();
    StartOpening();
    StatusStub();
}

/*
=====================
StartOpening

Starts the opening: the camera move of the studio, the wheel, the letters flying in.
=====================
*/
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
    MakeObj(0, 0, DrawOpeningStudio, 0x8000000);
    MakeObj(0, 0, DrawSearchlights, 0x8000000);
    for (i = 0; i < 14; i++) {
        task = CreatProc(TitleLetterProc, 0x8010000);
        task->data->titleLetterProc.index = i;
        obj = MakeObj(task, titleLetters[i].dl, DrawOpeningPiece, 0x8010000);
        obj->mtx = titleLetters[i].mtx;
    }
    task = CreatProc(OpeningWheelProc, 0x8010000);
    obj = MakeObj(task, wheelLightsDl, DrawOpeningWheel, 0x8010000);
    obj->y = -20;
    task = CreatProc(OpeningProc, 0x8000000);
    obj = MakeObj(task, openingHubDl, DrawOpeningHub, 0x8010000);
    task->data->opening.x = -272.0f;
    task->data->opening.y = 306.0f;
    task->data->opening.z = -411.0f;
    obj->x = -272;
    obj->y = 306;
    obj->z = -411;
    obj->roll = -61.317f;
    obj->pitch = 58.385f;
    obj->heading = -9.848f;
    hubAngle = 0;
    task->data->opening.music = PlaySound(15);
    for (i = 0; i < 24; i++) {
        task = CreatProc(OpeningWedgeProc, 0x8010000);
        task->data->openingWedge.index = i;
        obj = MakeObj(task, openingWedgeDls[i], DrawOpeningPiece, 0x8010000);
        obj->mtx = openingWedgeMtxs[i];
    }
    MakeObj(0, 0, DrawPressStart, 0x5000000);
    openingFrames = 721;
    logoSpread = 0;
}
