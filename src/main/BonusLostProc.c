#include "wof.h"

/*
=====================
BonusLostProc

The bonus puzzle was not solved: the camera, then ShowTotalProc.
=====================
*/
struct procResult_s BonusLostProc(proc_t *proc) {
    s32 event;
    struct procResult_s ret;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    ret.w[1] = 1;
    ret.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            ret.w[0] = 30 / frameRetraces;
            return ret;
        }
    }
    SetCameraView(20);
    CreatProc(ShowTotalProc, 0x6000000);
    ret.w[1] = 0;
    ret.w[0] = 0;
    return ret;
}
