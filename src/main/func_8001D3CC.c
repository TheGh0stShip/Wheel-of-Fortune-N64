#include "wof.h"

void func_8001D3CC(s32 arg0) {
    proc_t *obj;
    s32 unused;   /* NOTE: unused in the original */
    s32 unused2;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    obj = (proc_t *)func_8000A56C((s32)func_8001C584, arg0 | 0x2030000);
    ((playerProc_t *)obj->unk_30)->player = arg0;
    ((playerProc_t *)obj->unk_30)->unk_0C = D_800B8298;
}
