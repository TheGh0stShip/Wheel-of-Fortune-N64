#include "wof.h"

void func_8001D3CC(s32 arg0) {
    proc_t *obj;
    s32 unused;   /* NOTE: unused in the original */
    s32 unused2;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    obj = func_8000A56C(func_8001C584, arg0 | 0x2030000);
    obj->unk_30->playerProc.player = arg0;
    obj->unk_30->playerProc.unk_0C = D_800B8298;
}
