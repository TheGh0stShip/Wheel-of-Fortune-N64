#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
} Info;

void func_8002EBF4(void) {
    proc_t *task;

    func_800087F8();
    func_8000A56C((s32)&func_8001228C, 0x1020000);
    task = (proc_t *)func_8000A56C((s32)&func_8002E0C8, 0x5020000);
    ((Info *)task->unk_30)->unk_04 = 6;
}
