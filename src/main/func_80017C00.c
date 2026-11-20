#include "wof.h"

void func_80017C00(s32 arg0, s32 arg1) {
    obj_t *sp10;
    proc_t *task;

    sp10 = FindObj(0x3000000, 0xFF000000);
    task = FindProc(0x2010000, 0xFFFF0000);
    if (task != 0) {
        KillProc(task, 1);
    }
    switch (arg0) {
    case 0:
        func_80016944(sp10, D_800581FC[D_800FB808]);
        return;
    case 1:
        task = FindProc(0x2010000, 0xFFFF0000);
        if (task == 0 && arg1 == 0) {
            task = CreatProc(func_80017938, D_800FB808 | 0x2010000);
            task->unk_30->data80017938.unk_04 = D_800FB808;
        }
        func_80016944(sp10, arg0);
        return;
    case 3:
        if (D_800B619C == 2) {
            func_80016944(sp10, 18);
        } else {
            func_80016944(sp10, arg0);
        }
        return;
    }
    func_80016944(sp10, arg0);
}
