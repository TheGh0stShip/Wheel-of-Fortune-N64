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
    s32 sp24;

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
            sp24 = PlaySound(8);
            break;
        case 2:
            sp24 = PlaySound(9);
            break;
        case 3:
            sp24 = PlaySound(10);
            break;
        default:
            sp24 = PlaySound(guRandom() % 3 + 16);
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
