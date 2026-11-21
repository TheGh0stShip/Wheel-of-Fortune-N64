// wof_movieproc.c -- the procs that play a movie on the screen and as a contestant's picture
//
// MovieProc ends off an 8-byte boundary with ClipProc right after, which happens only inside an object.
// Whether UpdateClip before it and LoadMovie after it are this object's the text does not say.

#include "wof.h"

/*
=====================
MovieProc

Plays a movie on the screen; at its end, its event.
=====================
*/
struct procResult_s MovieProc(proc_t *proc) {
    s32 event;
    struct procResult_s ret;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    ret.w[1] = 1;
    ret.w[0] = 0;
    for (;;) {
        event = ProcGetMessage(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            if (proc->data->moviePlay.sound > 0) {
                movieSound = proc->data->moviePlay.sound;
            }
            minRetraces = 4;
            break;
        case 34:
            ret.w[1] = 0;
            ret.w[0] = 1;
            return ret;
        }
    }
    UpdateMovie(proc);
    if (movieDone != 0) {
        PopMemStack(1);
        minRetraces = 0;
        ret.w[1] = 0;
        ret.w[0] = 1;
        if (movieDone == 2) {
            func_800A4E58(0);
            PlayMovie(curMovie, proc->data->moviePlay.event, proc->data->moviePlay.obj->x, proc->data->moviePlay.obj->y);
        } else if (proc->data->moviePlay.event != 0) {
            ProcPostEvent(proc->data->moviePlay.event);
        }
    }
    return ret;
}

/*
=====================
ClipProc

Plays a movie as a contestant's picture; at its end, its event.
=====================
*/
struct procResult_s ClipProc(proc_t *proc) {
    s32 event;
    struct procResult_s result;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            if (proc->data->clipPlay.sound > 0) {
                movieSound = proc->data->clipPlay.sound;
            }
            minRetraces = 8;
            break;
        case 34:
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
    }
    UpdateClip(proc);
    if (movieDone != 0) {
        SetGameView(3, 0);
        movieToMemory = 0;
        PopMemStack(1);
        minRetraces = 0;
        result.w[1] = 0;
        result.w[0] = 1;
        InitAnim(1, proc->data->clipPlay.slot);
        if (proc->data->clipPlay.event != 0) {
            ProcPostEvent(proc->data->clipPlay.event);
        }
    }
    return result;
}
