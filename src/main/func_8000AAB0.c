#include "wof.h"


void func_8000AAB0(proc_t *proc, s32 arg1, s32 arg2) {
    if (proc == 0) {
        func_80009F38("ProcPostMessage: NULL proc\n");
        return;
    }
    if (arg1 >= 53) {
        func_80009F38("ProcPostMessage: bogus message\n");
        return;
    }
    if (proc->count < 5) {
        proc->items[proc->count] = arg1;
        proc->count++;
        if (arg2 != 0) {
            proc->unk_14 = 0;
            proc->unk_0C = 0;
        }
        return;
    }
    func_80009F38("ProcPostMessage: Message Que overrun.\n");
}
