// wof_anim.c -- the draw functions of the contestants and Vanna, and their pictures and animations:
// their clips, decoded once from the movies, and the procs that play them
//
// The object starts after the 4-byte gap that ends StartDemoTimer. Its read-only data opens with the
// RCS run at 0x80001960, which could open an object starting after DrawContestant or DrawVanna instead;
// that it opens at the gap, so that DrawContestant to DrawVanna are this object's, rests on the RCS
// premise (every object from 0x8000BAA8 on opens its read-only data with an RCS run, which the project
// accepts). Inside, DrawMenuContestant, SetPicture, SetVannaPicture, AnimProc, VannaAnimProc,
// SetVannaStill, InitVannaAnim, PlayContestantClip and InitMenuContestants end off an 8-byte boundary
// with the next function right after, which happens only inside an object; InitMenuAnim, InitAnim and
// the functions to InitContestants share string literals or lie among each other's read-only items and
// data. Where it ends after HideOtherContestants the text does not say: the RCS runs at 0x80001A30,
// 0x80001A48 and 0x80001A60 open the next objects at three of the positions after
// HideOtherContestants, PauseGame, PauseProc, StartPauseProc (a text gap), StartApplause, DrawConfetti
// and ConfettiProc.

#include "wof.h"

// The #ident line of the system header this object included: the original assembler put the string
// into the read-only data, which it opens. The header is not in this tree, so its line stands here.
#ident "$Revision: 1.17 $"

/*
=====================
DrawContestant

The draw function of a player's contestant.
=====================
*/
void DrawContestant(obj_t *obj, frame_t *frame) {
    if (obj->image == 0) {
        return;
    }
    switch (IsBoardView()) {
    case 0:
        gSPLightColor(glistp++, LIGHT_3, 0xCCCCCCCC);
        gSPLightColor(glistp++, LIGHT_4, 0xCCCCCCCC);
        gSPTexture(glistp++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
        gDPPipeSync(glistp++);
        gDPSetRenderMode(glistp++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);
        gDPSetCombineMode(glistp++, G_CC_MODULATERGBDECALA, G_CC_MODULATERGBDECALA);
        gDPLoadTextureBlock(glistp++, obj->image, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 64, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, 6, G_TX_NOLOD, G_TX_NOLOD);
        gDPPipeSync(glistp++);
        gSPDisplayList(glistp++, obj->dl);
        gDPLoadTextureBlock(glistp++, obj->image + 0x1000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 64, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, 6, G_TX_NOLOD, G_TX_NOLOD);
        gSPDisplayList(glistp++, obj->secondDl);
        gDPPipeSync(glistp++);
        SetLightColor(3);
        SetLightColor(4);
        gDPSetRenderMode(glistp++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    }
}

/*
=====================
DrawMenuContestant

The draw function of a contestant in the menus.
=====================
*/
void DrawMenuContestant(obj_t *obj, frame_t *frame) {
    if (obj->image == 0) {
        return;
    }
    guTranslate(&frame->translate[obj->index], (f32)obj->x, (f32)obj->y, (f32)obj->z);
    guScale(&frame->scale[obj->index], obj->scale, obj->scale, obj->scale);
    guRotateRPY(&frame->rotate[obj->index], obj->roll, obj->pitch, obj->heading);
    gSPMatrix(glistp++, &frame->translate[obj->index], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &frame->scale[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPDisplayList(glistp++, D_010219C8);
    gSPTexture(glistp++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPPipeSync(glistp++);
    gDPSetRenderMode(glistp++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);
    gDPSetCombineMode(glistp++, G_CC_MODULATERGBDECALA, G_CC_MODULATERGBDECALA);
    gDPLoadTextureBlock(glistp++, obj->image, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 64, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                        5, 6, G_TX_NOLOD, G_TX_NOLOD);
    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, obj->dl);
    gDPLoadTextureBlock(glistp++, obj->image + 0x1000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 64, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                        5, 6, G_TX_NOLOD, G_TX_NOLOD);
    gSPDisplayList(glistp++, obj->secondDl);
    gDPPipeSync(glistp++);
    gDPSetRenderMode(glistp++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
}

/*
=====================
DrawVanna

The draw function of Vanna.
=====================
*/
void DrawVanna(obj_t *obj, frame_t *frame) {
    proc_t *actor;
    s16 *pixels;

    if (obj->image == 0) {
        return;
    }
    if (gameMode == 6) {
        actor = FindProc(0xA000400, -1);
        if (actor != 0) {
            pixels = actor->data->vannaAnim.pictures + actor->data->vannaAnim.frame * ( 64 * 96 );
            SetVannaPicture(pixels, actor->data->vannaAnim.mirror * lightDir);
        }
    }
    gSPMatrix(glistp++, &D_0113AE28, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    guTranslate(&frame->translate[obj->index], obj->x, obj->y, obj->z);
    gSPMatrix(glistp++, &frame->translate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPTexture(glistp++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPPipeSync(glistp++);
    gDPSetRenderMode(glistp++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);
    gDPSetCombineMode(glistp++, G_CC_MODULATERGBDECALA, G_CC_MODULATERGBDECALA);
    gDPLoadTextureBlock(glistp++, obj->image, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                        6, 5, G_TX_NOLOD, G_TX_NOLOD);
    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, D_0113AD08);
    gDPLoadTextureBlock(glistp++, obj->image + 0x1000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                        6, 5, G_TX_NOLOD, G_TX_NOLOD);
    gSPDisplayList(glistp++, D_0113AD28);
    gDPLoadTextureBlock(glistp++, obj->image + 0x2000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                        6, 5, G_TX_NOLOD, G_TX_NOLOD);
    gSPDisplayList(glistp++, D_0113AD48);
    gDPPipeSync(glistp++);
    gDPSetRenderMode(glistp++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
}

Gfx *contestantDls[3][2] = {
    { (Gfx *)0x0113A9F0, (Gfx *)0x0113AA18 },
    { (Gfx *)0x0113AA80, (Gfx *)0x0113AAA8 },
    { (Gfx *)0x0113AA38, (Gfx *)0x0113AA60 }
};
clip_t contestantClips[6][2] = {
    {
        { 64, 64, 8, 4, 1, 0, NULL, 13, contestant0AnimMask },
        { 64, 64, 1, 4, 2, 0, NULL, 27, contestant0StillMask }
    },
    {
        { 64, 64, 9, 4, 2, 0, NULL, 15, contestant1AnimMask },
        { 64, 64, 1, 4, 2, 0, NULL, 28, contestant1StillMask }
    },
    {
        { 64, 64, 8, 4, 2, 0, NULL, 16, contestant2AnimMask },
        { 64, 64, 1, 4, 2, 0, NULL, 29, contestant2StillMask }
    },
    {
        { 64, 64, 6, 4, 2, 0, NULL, 17, contestant3AnimMask },
        { 64, 64, 1, 4, 2, 0, NULL, 30, contestant3StillMask }
    },
    {
        { 64, 64, 10, 4, 2, 0, NULL, 18, contestant4AnimMask },
        { 64, 64, 1, 4, 2, 0, NULL, 31, contestant4StillMask }
    },
    {
        { 64, 64, 7, 4, 2, 0, NULL, 20, contestant5AnimMask },
        { 64, 64, 1, 4, 2, 0, NULL, 32, contestant5StillMask }
    }
};
clip_t contestantMovies[6][2] = {
    {
        { 0, 0, -1, 0, 0, 0, NULL, 0, NULL },
        { 64, 64, 9, 4, 0, 0, NULL, 14, contestant0ClipMask1 }
    },
    {
        { 0, 0, -1, 0, 0, 0, NULL, 0, NULL },
        { 0, 0, -1, 0, 0, 0, NULL, 0, NULL }
    },
    {
        { 64, 64, 8, 4, 2, 0, NULL, 34, contestant2ClipMask0 },
        { 0, 0, -1, 0, 0, 0, NULL, 0, NULL }
    },
    {
        { 64, 64, 6, 4, 2, 0, NULL, 35, contestant3ClipMask0 },
        { 0, 0, -1, 0, 0, 0, NULL, 0, NULL }
    },
    {
        { 64, 64, 10, 4, 2, 0, NULL, 36, contestant4ClipMask0 },
        { 64, 64, 10, 4, 2, 0, NULL, 37, contestant4ClipMask1 }
    },
    {
        { 64, 64, 4, 4, 2, 0, NULL, 19, contestant5ClipMask0 },
        { 0, 0, -1, 0, 0, 0, NULL, 0, NULL }
    }
};
clip_t menuClips[6] = {
    { 64, 64, 1, 4, 2, 0, NULL, 27, contestant0StillMask },
    { 64, 64, 1, 4, 2, 0, NULL, 28, contestant1StillMask },
    { 64, 64, 1, 4, 2, 0, NULL, 29, contestant2StillMask },
    { 64, 64, 1, 4, 2, 0, NULL, 30, contestant3StillMask },
    { 64, 64, 1, 4, 2, 0, NULL, 31, contestant4StillMask },
    { 64, 64, 1, 4, 2, 0, NULL, 32, contestant5StillMask }
};
clip_t vannaClips[6] = {
    { 64, 96, 8, 6, 2, 1, NULL, 21, vannaWalkMask },
    { 64, 96, 9, 6, 2, 1, NULL, 24, vannaAnim1Mask },
    { 64, 96, 7, 4, 3, 1, NULL, 25, vannaAnim2Mask },
    { 64, 96, 4, 6, 0, 1, NULL, 26, vannaTurnMask },
    { 64, 96, 1, 1, 3, 1, NULL, 24, vannaAnim1Mask },
    { 64, 96, 5, 6, 2, 1, NULL, 33, vannaAnim5Mask }
};
s32 vannaWalkOffsets[13] = { 0, -5, -1, 3, -2, -6, -4, 1, -1, 0, 2, 8, 9 };
s32 vannaTurnOffsets[3] = { 0, 2, 8 };
s32 columnLeftEdges[1] = { 9 };
s32 columnRightEdges[15] = {
    0, 71, 142, 213, 284, 355, 426, 497, 568, 639, 710, 781, 852, 923, 994
};

/*
=====================
SetPicture

Copies a picture into a picture slot of both frames.
=====================
*/
void SetPicture(s16 *pixels, s32 slot) {
    s32 i;
    s32 unused;   /* NOTE: unused in the original */
    s32 unused2;  /* NOTE: unused in the original */
    s32 unused3;  /* NOTE: unused in the original */
    u16 *src;
    s16 *dst1;
    s16 *dst2;

    src = (u16 *)pixels;
    dst1 = gfxInfo[0].frame.clipPictures[slot];
    dst2 = gfxInfo[1].frame.clipPictures[slot];
    for (i = 0; i < 0x1000; i++) {
        dst1[i] = src[i];
        dst2[i] = src[i];
    }
}

/*
=====================
SetVannaPicture

Copies Vanna's picture into this frame, mirrored for -1.
=====================
*/
void SetVannaPicture(s16 *pixels, s32 dir) {
    s32 i;
    s32 j;
    s32 k;
    s32 unused;  /* NOTE: unused in the original */
    u16 *src;
    s16 *dst;

    src = (u16 *)pixels;
    dst = gfxInfo[curGfxInfo].frame.vannaPicture;
    if (dir == -1) {
        for (i = 0; i < 96; i++) {
            k = 63;
            for (j = 0; j < 64; j++) {
                dst[i * 64 + j] = src[i * 64 + k];
                k--;
            }
        }
        return;
    }
    i = 0;
    while (i < 0x1800) {
        dst[i] = src[i];
        i++;
    }
}

/*
=====================
AnimProc

Plays a contestant's animation.
=====================
*/
struct procResult_s AnimProc(proc_t *proc) {
    struct procResult_s result;
    s32 event;
    obj_t *sprite;
    s32 offset;
    s32 index;
    s16 *addr;
    s32 base;

    base = 0x2000000;
    sprite = proc->data->anim.obj;
    index = proc->data->anim.slot;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            proc->data->anim.timer = 0;
            proc->data->anim.frame = 0;
            proc->data->anim.step = 1;
            break;
        }
    }
    if (IsBoardView() != 0 && gameMode != 7) {
        result.w[1] = 1;
        result.w[0] = 0;
        return result;
    }
    addr = proc->data->anim.pictures + proc->data->anim.frame * ( 64 * 64 );
    SetPicture(addr, index);
    offset = osVirtualToPhysical(&gfxInfo[curGfxInfo].frame.clipPictures[index]);
    offset = offset - osVirtualToPhysical(&gfxInfo[curGfxInfo].frame);
    sprite->image = base + offset;
    proc->data->anim.timer += frameRetraces;
    if (proc->data->anim.timer >= 4) {
        proc->data->anim.timer %= 4;
        proc->data->anim.frame += proc->data->anim.step;
        if (proc->data->anim.frame < 0) {
            if (proc->data->anim.loop != 0) {
                proc->data->anim.frame = 1;
                proc->data->anim.step = 1;
            } else {
                result.w[1] = 0;
                result.w[0] = 0;
                return result;
            }
        } else if (proc->data->anim.frame >= proc->data->anim.count) {
            if (proc->data->anim.loop == 1) {
                proc->data->anim.frame = proc->data->anim.count - 2;
                proc->data->anim.step = -1;
            } else if (proc->data->anim.loop == 2) {
                proc->data->anim.frame = 0;
                proc->data->anim.step = 1;
            } else {
                result.w[1] = 0;
                result.w[0] = 0;
                return result;
            }
        }
    }
    result.w[1] = 1;
    result.w[0] = 0;
    return result;
}

/*
=====================
VannaAnimProc

Plays Vanna's animation.
=====================
*/
struct procResult_s VannaAnimProc(proc_t *proc) {
    struct procResult_s ret;
    s32 event;
    obj_t *obj;
    s32 diff;
    s32 slot;  /* NOTE: read from the data and never used, as AnimProc uses its slot */
    s32 i;
    s32 unused;  /* NOTE: unused in the original */
    s16 *frame;
    s32 base;

    base = 0x2000000;
    obj = proc->data->vannaAnim.obj;
    slot = proc->data->vannaAnim.slot;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            proc->data->vannaAnim.timer = 0;
            proc->data->vannaAnim.frame = 0;
            proc->data->vannaAnim.step = 1;
            switch (proc->data->vannaAnim.anim) {
            case 0:
                vannaX = vannaX + (lightDir * 40);
                break;
            case 80:
                proc->data->vannaAnim.frame = proc->data->vannaAnim.count - 1;
                proc->data->vannaAnim.step = -1;
                proc->data->vannaAnim.loop = 0;
                break;
            }
            break;
        }
    }
    diff = osVirtualToPhysical(gfxInfo[curGfxInfo].frame.vannaPicture);
    diff = diff - osVirtualToPhysical(&gfxInfo[curGfxInfo].frame);
    obj->image = base + diff;
    proc->data->vannaAnim.timer = proc->data->vannaAnim.timer + frameRetraces;
    if (proc->data->vannaAnim.timer >= proc->data->vannaAnim.frameTime) {
        proc->data->vannaAnim.timer = proc->data->vannaAnim.timer % proc->data->vannaAnim.frameTime;
        proc->data->vannaAnim.frame = proc->data->vannaAnim.frame + proc->data->vannaAnim.step;
        if (proc->data->vannaAnim.frame < 0) {
            if (proc->data->vannaAnim.loop != 0) {
                proc->data->vannaAnim.frame = 1;
                proc->data->vannaAnim.step = 1;
            } else {
                InitVannaAnim(4, 0);
                ret.w[1] = 0;
                ret.w[0] = 1;
                return ret;
            }
        } else {
            if (proc->data->vannaAnim.frame >= proc->data->vannaAnim.count) {
                if (proc->data->vannaAnim.loop == 1) {
                    proc->data->vannaAnim.frame = proc->data->vannaAnim.count - 2;
                    proc->data->vannaAnim.step = -1;
                } else {
                    if (proc->data->vannaAnim.loop == 2) {
                        if (proc->data->vannaAnim.anim == 1) {
                            InitVannaAnim(5, 0);
                            ret.w[1] = 0;
                            ret.w[0] = 1;
                            return ret;
                        } else {
                            proc->data->vannaAnim.frame = 0;
                        }
                        proc->data->vannaAnim.step = 1;
                    } else {
                        if (proc->data->vannaAnim.loop == 3) {
                            proc->data->vannaAnim.frame = proc->data->vannaAnim.count - 1;
                            proc->data->vannaAnim.step = 0;
                        } else {
                            if (proc->data->vannaAnim.loop < 0) {
                                vannaX = vannaX + (lightDir * 44);
                                InitVannaAnim(0, 0);
                                ret.w[1] = 0;
                                ret.w[0] = 1;
                                return ret;
                            } else {
                                switch (proc->data->vannaAnim.anim) {
                                case 3:
                                    ProcPostEvent(49);
                                    vannaX = vannaX + (lightDir * 44);
                                    lightDir = lightDir * -1;
                                    break;
                                }
                                InitVannaAnim(4, 0);
                                ret.w[1] = 0;
                                ret.w[0] = 1;
                                return ret;
                            }
                        }
                    }
                }
            }
        }
        if (proc->data->vannaAnim.anim != 0) {
            goto L384;
        }
        i = 1;
        while (i < 15) {
            if (vannaX < columnRightEdges[i]) {
                if (vannaX > columnLeftEdges[i]) {
                    TurnSquares(i - 1);
                }
            }
            i++;
        }
        vannaX = vannaX + (lightDir * 24);
    } else {
L384: ;
    }
    frame = proc->data->vannaAnim.pictures + (proc->data->vannaAnim.frame * ( 64 * 96 ));
    SetVannaPicture(frame, (proc->data->vannaAnim.mirror * lightDir));
    switch (proc->data->vannaAnim.anim) {
    case 0:
        obj->x = vannaWalkOffsets[proc->data->vannaAnim.frame] * 4 * lightDir + vannaX;
        if (((lightDir == 1) && ((vannaX >= 921) && (proc->data->vannaAnim.frame == 1))) || ((lightDir == -1) && ((vannaX < 100) && (proc->data->vannaAnim.frame == 1)))) {
            InitVannaAnim(3, 0);
            ret.w[1] = 0;
            ret.w[0] = 1;
            return ret;
        }
        break;
    case 3:
        obj->x = vannaTurnOffsets[proc->data->vannaAnim.frame] * 4 * lightDir + vannaX;
        break;
    }
    ret.w[1] = 1;
    ret.w[0] = 0;
    return ret;
}

/*
=====================
InitMenuAnim

InitAnim for a contestant shown in the menus, with its obj; prints InitAnim's first message.
=====================
*/
void InitMenuAnim(s32 contestant, s32 slot, s32 x, s32 y, s32 z) {
    proc_t *task;
    obj_t *obj;

    if (contestant < 0) {
        return;
    }
    if (contestant >= 6) {
        FatalError("InitAnim: invalid animation number");
    }
    if (menuClips[contestant].pictures == 0) {
        return;
    }
    task = FindProc(slot | 0xA000300, -1);
    if (task != 0) {
        KillProc(task, 0);
    }
    task = CreatProc(AnimProc, slot | 0xA000300);
    obj = MakeObj(task, D_0113A9B0, DrawMenuContestant, slot | 0xA020000);
    obj->secondDl = D_0113A9D0;
    obj->x = x;
    obj->y = y;
    obj->z = z;
    task->data->anim.slot = slot;
    task->data->anim.pictures = menuClips[contestant].pictures;
    task->data->anim.count = menuClips[contestant].count;
    task->data->anim.loop = menuClips[contestant].loop;
    task->data->anim.obj = obj;
}

/*
=====================
InitAnim

Starts a player's contestant playing one of its two animations.
=====================
*/
void InitAnim(s32 anim, s32 player) {
    proc_t *task;
    obj_t *obj;
    s32 kind;

    if (anim < 0) {
        return;
    }
    if (anim >= 2) {
        FatalError("InitAnim: invalid animation number");
    }
    kind = players[player].contestant;
    if (kind >= 6) {
        FatalError("InitAnim: invalid contestant number");
    }
    if (contestantClips[kind][anim].pictures == 0) {
        return;
    }
    obj = FindObj(player | 0xA020000, -1);
    if (obj == 0) {
        FatalError("InitAnim: cannot find contestant obj");
    }
    task = FindProc(player | 0xA000300, -1);
    if (task != 0) {
        KillProc(task, 0);
    }
    task = CreatProc(AnimProc, player | 0xA000300);
    task->data->anim.slot = player;
    task->data->anim.pictures = contestantClips[kind][anim].pictures;
    task->data->anim.count = contestantClips[kind][anim].count;
    task->data->anim.loop = contestantClips[kind][anim].loop;
    task->data->anim.obj = obj;
}

/*
=====================
SetVannaStill

Shows Vanna standing still: animation 4, one picture.
=====================
*/
void SetVannaStill(void) {
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    SetVannaAnim(4);
}

/*
=====================
InitVannaAnim

Starts Vanna playing an animation; animation 80 is animation 2 of the bonus round.
=====================
*/
proc_t *InitVannaAnim(s32 anim, s32 replace) {
    proc_t *task;
    obj_t *child;
    s32 id;

    id = anim;
    if (anim < 0) {
        return;
    }
    if (anim == 80) {
        anim = 2;
    } else if (anim >= 6) {
        FatalError("InitVannaAnim: invalid animation number");
    }
    if (vannaClips[anim].pictures == 0) {
        return 0;
    }
    if (replace != 0) {
        KillProcClass(0xA000400, -1, 1);
        FreeObjClass(0xA030000, -1);
    }
    task = CreatProc(VannaAnimProc, 0xA000400);
    child = MakeObj(task, 0, DrawVanna, 0xA030000);
    child->x = vannaX;
    task->data->vannaAnim.anim = id;
    task->data->vannaAnim.pictures = vannaClips[anim].pictures;
    task->data->vannaAnim.count = vannaClips[anim].count;
    task->data->vannaAnim.frameTime = vannaClips[anim].frameTime;
    task->data->vannaAnim.loop = vannaClips[anim].loop;
    task->data->vannaAnim.mirror = vannaClips[anim].mirror;
    task->data->vannaAnim.obj = child;
    return task;
}

/*
=====================
SetVannaAnim

InitVannaAnim in place of the animation playing.
=====================
*/
void SetVannaAnim(s32 anim) {
    InitVannaAnim(anim, 1);
}

/*
=====================
PlayContestantAnims

Plays animation 0 of each of the three contestants.
=====================
*/
void PlayContestantAnims(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        InitAnim(0, i);
    }
}

/*
=====================
SetContestantsStill

Shows each of the three contestants still: animation 1, one picture.
=====================
*/
void SetContestantsStill(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        InitAnim(1, i);
    }
}

/*
=====================
InitContestants

Decodes the animations of the three contestants and of Vanna into memory and makes the contestants'
objs.
=====================
*/
void InitContestants(void) {
    obj_t *obj;
    s32 unused;  /* NOTE: unused in the original */
    clip_t *slots;
    s32 i;
    s32 j;
    s32 size;
    s32 base;

    base = 0x2000000;
    if (gameMode == 3) {
        for (i = 0; i < 3; i++) {
            players[i].contestant = i;
        }
    }
    contestantMemMark = PushMemStack();
    for (i = 0; i < 3; i++) {
        if (players[i].contestant >= 6) {
            FatalError("InitContestants: invalid image num");
        }
        slots = contestantClips[players[i].contestant];
        for (j = 0; j < 2; j++) {
            if (slots[j].count > 0) {
                size = slots[j].width * slots[j].height * 2;
                slots[j].pictures = AllocMem(size * slots[j].count);
                DecodeMovie(slots[j].movie, slots[j].count, slots[j].pictures, slots[j].mask);
            } else {
                slots[j].pictures = 0;
            }
        }
    }
    i = 0;
    while (i < 6) {
        size = vannaClips[i].width * vannaClips[i].height * 2;
        vannaClips[i].pictures = AllocMem(size * vannaClips[i].count);
        DecodeMovie(vannaClips[i].movie, vannaClips[i].count, vannaClips[i].pictures, vannaClips[i].mask);
        i++;
    }
    lightDir = 1;
    vannaX = 0;
    for (i = 0; i < 3; i++) {
        obj = MakeObj(0, contestantDls[i][0], DrawContestant, i | 0xA020000);
        obj->secondDl = contestantDls[i][1];
        obj->image = 0;
    }
    PlayContestantAnims();
    SetVannaAnim(4);
    retraceCount = 0;
}

/*
=====================
PlayContestantClip

Plays a movie as a player's picture, if the contestant has one; prints InitContestants' and
InitAnim's messages.
=====================
*/
s32 PlayContestantClip(s32 clip, s32 event, s32 player) {
    obj_t *obj;
    proc_t *other;
    s32 unused;  /* NOTE: unused in the original */
    clip_t *slots;
    s32 unused2;  /* NOTE: unused in the original */
    s32 unused3;  /* NOTE: unused in the original */
    s32 unused4;  /* NOTE: unused in the original */
    s32 base;

    base = 0x2000000;
    if (players[player].contestant >= 6) {
        FatalError("InitContestants: invalid image num");
    }
    slots = contestantMovies[players[player].contestant];
    if (slots[clip].count > 0) {
        obj = FindObj(player | 0xA020000, -1);
        if (obj == 0) {
            FatalError(noContestantObjMsg);
        }
        other = FindProc(player | 0xA000300, -1);
        if (other != 0) {
            KillProc(other, 0);
        }
        PlayClip(slots[clip].movie, slots[clip].mask, obj, player, event);
        return 1;
        return; /* dead, kept for the match */
    }
    return 0;
}

/*
=====================
InitMenuContestants

Decodes the movies of the six contestants of the menus.
=====================
*/
void InitMenuContestants(void) {
    s32 unused;  /* NOTE: unused in the original */
    s32 unused2;  /* NOTE: unused in the original */
    s32 i;
    s32 size;
    s32 base;

    base = 0x2000000;
    contestantMemMark = PushMemStack();
    for (i = 0; i < 6; i++) {
        size = menuClips[i].width * menuClips[i].height * 2;
        menuClips[i].pictures = AllocMem(size * menuClips[i].count);
        DecodeMovie(menuClips[i].movie, menuClips[i].count, menuClips[i].pictures, menuClips[i].mask);
    }
    retraceCount = 0;
}

/*
=====================
HideOtherContestants

Frees the pictures of every player but the one whose turn it is.
=====================
*/
void HideOtherContestants(void) {
    s32 i;
    obj_t *obj;
    proc_t *task;

    for (i = 0; i < 3; i++) {
        if (i != curPlayer) {
            task = FindProc(i | 0xA000300, -1);
            if (task != 0) {
                KillProc(task, 1);
                obj = FindObj(i | 0xA020000, -1);
                if (obj != 0) {
                    FreeObj(obj);
                }
            }
        }
    }
}
