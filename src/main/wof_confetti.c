// wof_confetti.c -- confetti: its draw function and proc, a piece at a random place, a burst of them,
// and the celebration
//
// The joins after AddConfetti and ConfettiBurstProc rest on the RCS premise (every object from
// 0x8000BAA8 on opens its read-only data with an RCS run, which the project accepts). The game's text
// ends after StartCelebration. guess: the boundary after StartApplause and the joins after DrawConfetti
// and ConfettiProc. The RCS run at 0x80001A60 opens this object's read-only data after one of
// StartApplause, DrawConfetti and ConfettiProc; it goes after StartApplause because AddConfetti makes
// its piece with ConfettiProc and DrawConfetti, and the project's ruling takes the join everywhere else.

#include "wof.h"

// The #ident line of the system header this object included: the original assembler put the string
// into the read-only data, which it opens. The header is not in this tree, so its line stands here.
#ident "$Revision: 1.17 $"

/*
=====================
DrawConfetti

The draw function of a piece of confetti.
=====================
*/
void DrawConfetti(obj_t *obj, frame_t *frame) {
    s32 unused;  /* NOTE: unused in the original */

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, &imageSetupDl);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    gDPLoadTextureBlock(glistp++, obj->image, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                        G_TX_CLAMP, G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
    gDPPipeSync(glistp++);
    gSPTextureRectangle(glistp++, obj->x << 2, obj->y << 2,
                        (obj->x + 31) << 2, (obj->y + 31) << 2,
                        G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10);
}

s32 confettiTextures[4] = { 0x0101F7D0, 0x0101FFD0, 0x010207D0, 0x01020FD0 };
f32 confettiGravity = 0.02f;
f32 confettiDrag = 0.01f;

/*
=====================
ConfettiProc

A piece of confetti falling across the screen.
=====================
*/
struct procResult_s ConfettiProc(proc_t *proc) {
    struct procResult_s ret;
    s32 event;
    s32 i;
    obj_t *sprite;

    sprite = proc->data->confetti.sprite;
    while ((event = ProcGetMessage(proc)) != PRC_EVENT_NULL) {
        switch (event) {
        case PRC_EVENT_INIT:
            proc->data->confetti.timer = 0;
            proc->data->confetti.frame = 0;
            break;
        }
    }
    proc->data->confetti.timer += frameRetraces;
    if (proc->data->confetti.timer >= 4) {
        proc->data->confetti.timer %= 4;
        proc->data->confetti.frame++;
        if (proc->data->confetti.frame >= 4) {
            proc->data->confetti.frame = 0;
            proc->data->confetti.count--;
            if (proc->data->confetti.count < 0) {
                ret.w[1] = 0;
                ret.w[0] = 1;
                return ret;
            }
        }
    }
    i = 0;
    while (i < frameRetraces) {
        proc->data->confetti.vy += confettiGravity;
        proc->data->confetti.vx -= confettiDrag;
        proc->data->confetti.x += proc->data->confetti.vx;
        proc->data->confetti.y += proc->data->confetti.vy;
        i++;
    }
    sprite->x = (s32)proc->data->confetti.x;
    sprite->y = (s32)proc->data->confetti.y;
    if (sprite->x < 0 || sprite->y < 0 || sprite->x >= 321 || sprite->y >= 201) {
        ret.w[1] = 0;
        ret.w[0] = 1;
        return ret;
    }
    sprite->image = confettiTextures[proc->data->confetti.frame];
    ret.w[1] = 1;
    ret.w[0] = 0;
    return ret;
}

/*
=====================
AddConfetti

A piece of confetti at a random place, speed and count of turns.
=====================
*/
void AddConfetti(s32 x, s32 xRange, s32 y, s32 yRange, s32 speedRange, s32 speedBase, s32 turnsRange, s32 turnsBase) {
    obj_t *obj;
    proc_t *task;

    task = CreatProc(ConfettiProc, 0x5030000);
    obj = MakeObj(task, 0, DrawConfetti, 0x5030000);
    task->data->confetti.count = guRandom() % turnsRange - turnsBase + turnsBase;
    task->data->confetti.vx = (f32)(guRandom() % speedRange - speedBase + speedBase) / 100.0f;
    task->data->confetti.vy = 0;
    task->data->confetti.x = guRandom() % xRange + x;
    task->data->confetti.y = guRandom() % yRange + y;
}

/*
=====================
ConfettiBurstProc

Throws confetti for a while.
=====================
*/
struct procResult_s ConfettiBurstProc(proc_t *proc) {
    struct procResult_s result;
    s32 event;
    s32 i;
    obj_t *obj;

    obj = proc->data->obj;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == PRC_EVENT_NULL) {
            break;
        }
        switch (event) {
        case PRC_EVENT_INIT:
            proc->data->confettiBurst.countdown = 10;
            break;
        }
    }
    proc->data->confettiBurst.countdown--;
    if (proc->data->confettiBurst.countdown < 0) {
        if (proc->data->confettiBurst.countdown < -40) {
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
        if (proc->data->confettiBurst.countdown >= -9) {
            AddConfetti(80, 150, 60, 80, 30, 10, 2, 1);
        } else {
            AddConfetti(80, 150, 60, 80, 30, 10, 2, 1);
            result.w[1] = 1;
            result.w[0] = ((guRandom() % -1) * proc->data->confettiBurst.countdown) / frameRetraces;
            return result;
        }
    } else {
        i = 0;
        for (;;) {
            if (i >= 4) {
                break;
            }
            AddConfetti(52, 15, 27, 15, 300, 150, 6, 3);
            i++;
        }
    }
    result.w[1] = 1;
    result.w[0] = (guRandom() % 10) / frameRetraces;
    return result;
}

/*
=====================
StartCelebration

The movie and the confetti of a win.
=====================
*/
void StartCelebration(void) {
    curMask = celebrationMask;
    PlayMovie(0x16, PRC_EVENT_NULL, 0x28, 0xF);
    CreatProc(ConfettiBurstProc, 0x05030000);
}
