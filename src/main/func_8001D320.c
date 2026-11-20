#include "wof.h"


void func_8001D320(s32 arg0) {
    proc_t *task;
    s32 pad0;
    s8 pad1;

    task = (proc_t *)func_8000A56C((s32)&func_8001C584, arg0 | 0x2030000);
    ((data8001C584_t *)task->unk_30)->unk_04 = arg0;
    ((data8001C584_t *)task->unk_30)->unk_0C = 0.65f;
    D_800B9990[arg0].unk_014 = 4;
    func_80024D60(arg0);
}
