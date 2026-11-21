#include "wof.h"


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
