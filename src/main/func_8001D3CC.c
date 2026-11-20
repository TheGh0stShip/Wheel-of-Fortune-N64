#include "wof.h"

void func_8001D3CC(s32 arg0) {
    proc_t *obj;
    s32 pad0;
    s8 pad1;

    obj = (proc_t *)func_8000A56C((s32)func_8001C584, arg0 | 0x2030000);
    ((data8001C584_t *)obj->unk_30)->unk_04 = arg0;
    ((data8001C584_t *)obj->unk_30)->unk_0C = D_800B8298;
}
