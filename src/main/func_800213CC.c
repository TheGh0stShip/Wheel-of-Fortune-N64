#include "wof.h"

void func_800213CC(proc_t *proc) {
    s32 sp10;
    s32 unused;  /* NOTE: unused in the original */
    s32 unused2;  /* NOTE: unused in the original */
    s32 unused3;  /* NOTE: unused in the original */
    s32 unused4;  /* NOTE: unused in the original */
    s32 unused5;  /* NOTE: unused in the original */
    s32 unused6;  /* NOTE: unused in the original */
    s32 unused7;  /* NOTE: unused in the original */
    s32 unused8;  /* NOTE: unused in the original */
    s32 sp34;

    sp34 = 0x2000000;
    sp10 = osVirtualToPhysical(gfxInfo[curGfxInfo].frame.unk_0AC00[proc->data->data80021744.unk_10]);
    sp10 = sp10 - osVirtualToPhysical(&gfxInfo[curGfxInfo].frame);
    proc->data->data80021744.unk_00->image = sp34 + sp10;
    D_800B998C = gfxInfo[curGfxInfo].frame.unk_0AC00[proc->data->data80021744.unk_10];
    if (D_800B40C4 == 0) {
        D_800B40C4 = func_8009D244();
    }
}
