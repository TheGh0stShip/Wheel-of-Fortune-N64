// ConfettiProc.c -- a piece of confetti falling across the screen

#include "wof.h"

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
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
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
