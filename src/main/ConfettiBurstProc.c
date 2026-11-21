#include "wof.h"


struct procResult_s ConfettiBurstProc(proc_t *proc) {
    struct procResult_s sp20;
    s32 sp30;
    s32 sp34;
    obj_t *sp38;

    sp38 = proc->data->obj;
    for (;;) {
        sp30 = ProcGetMessage(proc);
        if (sp30 == 0) {
            break;
        }
        switch (sp30) {
        case 8:
            proc->data->confettiBurst.countdown = 10;
            break;
        }
    }
    proc->data->confettiBurst.countdown--;
    if (proc->data->confettiBurst.countdown < 0) {
        if (proc->data->confettiBurst.countdown < -40) {
            sp20.w[1] = 0;
            sp20.w[0] = 1;
            return sp20;
        }
        if (proc->data->confettiBurst.countdown >= -9) {
            AddConfetti(80, 150, 60, 80, 30, 10, 2, 1);
        } else {
            AddConfetti(80, 150, 60, 80, 30, 10, 2, 1);
            sp20.w[1] = 1;
            sp20.w[0] = ((guRandom() % -1) * proc->data->confettiBurst.countdown) / frameRetraces;
            return sp20;
        }
    } else {
        sp34 = 0;
        for (;;) {
            if (sp34 >= 4) {
                break;
            }
            AddConfetti(52, 15, 27, 15, 300, 150, 6, 3);
            sp34++;
        }
    }
    sp20.w[1] = 1;
    sp20.w[0] = (guRandom() % 10) / frameRetraces;
    return sp20;
}
