#include "wof.h"


void ProcPostMessage(proc_t *proc, s32 msg, s32 wake) {
    if (proc == 0) {
        func_80009F38("ProcPostMessage: NULL proc\n");
        return;
    }
    if (msg >= 53) {
        func_80009F38("ProcPostMessage: bogus message\n");
        return;
    }
    if (proc->count < 5) {
        proc->items[proc->count] = msg;
        proc->count++;
        if (wake != 0) {
            proc->unk_14 = 0;
            proc->unk_0C = 0;
        }
        return;
    }
    func_80009F38("ProcPostMessage: Message Que overrun.\n");
}
