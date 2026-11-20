#include "wof.h"

void func_8001D3CC(s32 arg0) {
    proc_t *task;
    s32 unused;   /* NOTE: unused in the original */
    s32 unused2;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    task = CreatProc(func_8001C584, arg0 | 0x2030000);
    task->data->playerProc.player = arg0;
    task->data->playerProc.unk_0C = D_800B8298;
}
