#include "wof.h"

void func_8000A664(void) {
    struct n64dk_r12 res;
    proc_t *task;

    task = &D_800B82A0[0];
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
                    func_8000A4A4((s32)task, res.w[0]);
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
