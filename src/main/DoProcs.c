#include "wof.h"

void DoProcs(void) {
    struct procResult_s res;
    proc_t *task;

    task = &procst[0];
    while (task->next != 0) {
        task = task->next;
        if (task->unk_00 == 0) {
            func_80009F38("DoProcs: Tried to execute a NULL\n");
            return;
        }
        if (task->unk_14 == 0) {
            if (task->unk_0C > 0) {
                if (D_800BCD54 != 6) {
                    task->unk_0C--;
                }
            } else {
                if (D_800BCD54 == 6) {
                    if (task->unk_08 == 0xB000000) {
                        res = task->unk_00(task);
                    }
                } else {
                    res = task->unk_00(task);
                }
                switch (res.w[1]) {
                case 0:
                    KillProc(task, res.w[0]);
                    break;
                case 1:
                    task->unk_0C = res.w[0];
                    break;
                case 2:
                    task->unk_10 = res.w[0];
                    task->unk_14 = 1;
                    break;
                case 3:
                    task->unk_10 = res.w[0];
                    break;
                }
            }
        }
    }
}
