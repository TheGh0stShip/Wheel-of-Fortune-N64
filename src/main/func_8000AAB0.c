#include "wof.h"


void func_8000AAB0(s32 arg0, s32 arg1, s32 arg2) {
    if (arg0 == 0) {
        func_80009F38("ProcPostMessage: NULL proc\n");
        return;
    }
    if (arg1 >= 53) {
        func_80009F38("ProcPostMessage: bogus message\n");
        return;
    }
    if (((proc_t *)arg0)->count < 5) {
        ((proc_t *)arg0)->items[((proc_t *)arg0)->count] = arg1;
        ((proc_t *)arg0)->count++;
        if (arg2 != 0) {
            ((proc_t *)arg0)->unk_14 = 0;
            ((proc_t *)arg0)->unk_0C = 0;
        }
        return;
    }
    func_80009F38("ProcPostMessage: Message Que overrun.\n");
}
