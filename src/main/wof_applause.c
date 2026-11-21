// wof_applause.c -- the crowd's applause
//
// ApplauseProc ends off an 8-byte boundary with StartApplause right after, which happens only inside an
// object; the 4-byte gap that ends StartPauseProc opens it. Whether it runs on into DrawConfetti the
// text does not say.

#include "wof.h"

// guess: the RCS run at 0x80001A48 opens this object's read-only data, and is all of it. The 4-byte
// gap after StartPauseProc ends an object for certain, and every object from wof_opening on whose
// start the evidence shows opens its read-only data with a run; the run at 0x80001A30 before this one
// then opens the pause's object, and the one at 0x80001A60 AddConfetti's. The bytes are the same if
// this run opens an object after StartApplause instead.
#ident "$Revision: 1.17 $"

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

/*
=====================
StartApplause

Creates ApplauseProc.
=====================
*/
void StartApplause(void) {
    CreatProc(ApplauseProc, 0x0C000000);
}
