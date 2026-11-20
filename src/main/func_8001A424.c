#include "wof.h"

void func_8001A424(s32 arg0) {
    proc_t *task;
    s32 unused;   /* NOTE: unused in the original */
    s32 unused2;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    task = func_8000A56C(func_80019AAC, arg0 | 0x2020000);
    task->unk_30->playerProc.player = arg0;
}
