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
    sp10 = osVirtualToPhysical(D_800BEF08[D_800B61A0].frame.unk_0AC00[((data80021744_t *)proc->unk_30)->unk_10]);
    sp10 = sp10 - osVirtualToPhysical(&D_800BEF08[D_800B61A0].frame);
    ((data80021744_t *)proc->unk_30)->unk_00->unk_44 = sp34 + sp10;
    D_800B998C = D_800BEF08[D_800B61A0].frame.unk_0AC00[((data80021744_t *)proc->unk_30)->unk_10];
    if (D_800B40C4 == 0) {
        D_800B40C4 = func_8009D244();
    }
}
