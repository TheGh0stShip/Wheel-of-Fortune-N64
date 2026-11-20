#include "wof.h"

void DoProcs(void) {
    struct procResult_s res;
    proc_t *task;

    task = &procst[0];
    while (task->next != 0) {
        task = task->next;
        if (task->handler == 0) {
            func_80009F38("DoProcs: Tried to execute a NULL\n");
            return;
        }
        if (task->waiting == 0) {
            if (task->sleep > 0) {
                if (gameMode != 6) {
                    task->sleep--;
                }
            } else {
                if (gameMode == 6) {
                    if (task->cls == 0xB000000) {
                        res = task->handler(task);
                    }
                } else {
                    res = task->handler(task);
                }
                switch (res.w[1]) {
                case 0:
                    KillProc(task, res.w[0]);
                    break;
                case 1:
                    task->sleep = res.w[0];
                    break;
                case 2:
                    task->event = res.w[0];
                    task->waiting = 1;
                    break;
                case 3:
                    task->event = res.w[0];
                    break;
                }
            }
        }
    }
}
