#include "wof.h"

struct procResult_s func_8001BC44(proc_t *proc) {
    struct procResult_s sp10;
    proc_t *task;
    s32 unused;  /* NOTE: unused in the original */
    s32 event;

    sp10.w[1] = 1;
    sp10.w[0] = 0;
    if (proc->data->playerProc.player != D_800FB808) {
        ProcClearMessages(proc);
        return sp10;
    }
    task = FindProc(0x1020000, -1);
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            func_8002EBF4();
            func_80017C00(3, 1);
            sp10.w[1] = 2;
            sp10.w[0] = 5;
            return sp10;
        case 5:
            if (func_800088E4() == 1) {
                ProcPostMessage(task, 19, 0);
                ProcPostEvent(24);
                ProcPostEvent(10);
                sp10.w[1] = 0;
                sp10.w[0] = 0;
            } else {
                ProcPostMessage(task, 20, 0);
                PlaySound(1);
                if (func_80017548() != 0) {
                    ProcPostEvent(10);
                    ProcPostEvent(24);
                }
                sp10.w[1] = 0;
                sp10.w[0] = 0;
                return sp10;
            }
            break;
        case 34:
            sp10.w[1] = 0;
            sp10.w[0] = 0;
            return sp10;
        }
    }
    return sp10;
}
