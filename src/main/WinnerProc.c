#include "wof.h"


struct procResult_s WinnerProc(proc_t *proc) {
    struct procResult_s ret;
    s32 unused;   /* NOTE: unused in the original */
    s32 unused2;  /* NOTE: unused in the original */
    s32 event;

    ret.w[1] = 1;
    ret.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            SetGameView(17, 0);
            func_80032B10();
            HideOtherContestants();
            applause += 3;
            if (players[curPlayer].unk_110 > 0) {
                PlaySound(players[curPlayer].unk_110);
            }
            ret.w[1] = 1;
            ret.w[0] = 45 / frameRetraces;
            return ret;
        }
    }
    if (curPlayer == 0) {
        PlayMovie(11, 42, 185, 20);
    } else {
        PlayMovieCorner(11, 42);
    }
    ret.w[1] = 0;
    ret.w[0] = 0;
    return ret;
}
