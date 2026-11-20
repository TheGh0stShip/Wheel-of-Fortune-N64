#include "wof.h"

void func_800212C0(proc_t *proc) {
    s32 diff;
    s32 unused;  /* NOTE: unused in the original */
    s32 unused2;  /* NOTE: unused in the original */
    s32 unused3;  /* NOTE: unused in the original */
    s32 unused4;  /* NOTE: unused in the original */
    s32 unused5;  /* NOTE: unused in the original */
    s32 unused6;  /* NOTE: unused in the original */
    s32 unused7;  /* NOTE: unused in the original */
    s32 unused8;  /* NOTE: unused in the original */
    s32 base;

    base = 0x2000000;
    diff = osVirtualToPhysical(gfxInfo[curGfxInfo].frame.unk_19C00);
    diff = diff - osVirtualToPhysical(&gfxInfo[curGfxInfo].frame);
    proc->data->data80021548.unk_00->image = base + diff;
    if (D_800B40C4 == 0) {
        D_800B40C4 = func_8009D244();
    }
}
