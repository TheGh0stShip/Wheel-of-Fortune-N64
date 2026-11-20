#include "wof.h"

void func_80017C00(s32 arg0, s32 arg1) {
    s32 sp10;
    s32 task;

    sp10 = func_8000B5DC(0x3000000, 0xFF000000);
    task = func_8000A990(0x2010000, 0xFFFF0000);
    if (task != 0) {
        func_8000A4A4(task, 1);
    }
    switch (arg0) {
    case 0:
        func_80016944(sp10, D_800581FC[D_800FB808]);
        return;
    case 1:
        task = func_8000A990(0x2010000, 0xFFFF0000);
        if (task == 0 && arg1 == 0) {
            task = func_8000A56C((s32)&func_80017938, D_800FB808 | 0x2010000);
            ((data80017938_t *)((proc_t *)task)->unk_30)->unk_04 = D_800FB808;
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
