// ApplauseProc.c -- plays the crowd's applause, as loud as applause asks

#include "wof.h"

/*
=====================
ApplauseProc

Plays the crowd's applause, as loud as applause asks.
=====================
*/
struct procResult_s ApplauseProc(proc_t *proc) {
    struct procResult_s result;
    s32 event;
    s32 slot;

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            PlaySound(10);
            applause = 2;
            proc->data->applauseProc.played = 0;
            proc->data->applauseProc.unk_08 = 0;
            break;
        }
    }
    if (proc->data->applauseProc.played > 0) {
        switch (proc->data->applauseProc.played) {
        case 1:
            slot = PlaySound(8);
            break;
        case 2:
            slot = PlaySound(9);
            break;
        case 3:
            slot = PlaySound(10);
            break;
        default:
            slot = PlaySound(guRandom() % 3 + 16);
        }
        if (applause == proc->data->applauseProc.played) {
            applause = 0;
            proc->data->applauseProc.played = 0;
        }
    }
    if (proc->data->applauseProc.played < applause) {
        proc->data->applauseProc.played++;
        result.w[0] = 10 / frameRetraces;
    }
    return result;
}
