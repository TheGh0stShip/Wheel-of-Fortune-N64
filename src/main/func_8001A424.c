#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
} Data;

void func_8001A424(s32 arg0) {
    proc_t *task;
    s32 pad0;
    s8 pad1;

    task = (proc_t *)func_8000A56C((s32)func_80019AAC, arg0 | 0x2020000);
    ((Data *)task->unk_30)->unk_04 = arg0;
}
