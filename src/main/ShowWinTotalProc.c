// ShowWinTotalProc.c -- shows the total of a bonus round won and a movie, then the credits

#include "wof.h"

/*
=====================
ShowWinTotalProc

Shows the total of a bonus round won and a movie, then the credits.
=====================
*/
struct procResult_s ShowWinTotalProc(proc_t *proc) {
    s32 event;
    struct procResult_s ret;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    ret.w[1] = 1;
    ret.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            gameMode = 8;
            ShowTotal();
            MakeScreenObj(proc, 0, func_80027F3C, 0x5050100);
            applause++;
            ret.w[0] = 30 / frameRetraces;
            return ret;
        case 46:
            CreatProc(CreditsProc, 0x6060000);
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        }
    }
    PlayMovieCorner(0, 46);
    ret.w[1] = 2;
    ret.w[0] = 46;
    return ret;
}
