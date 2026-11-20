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
    diff = osVirtualToPhysical(D_800BEF08[D_800B61A0].frame.unk_19C00);
    diff = diff - osVirtualToPhysical(&D_800BEF08[D_800B61A0].frame);
    ((data80021548_t *)proc->unk_30)->unk_00->unk_44 = base + diff;
    if (D_800B40C4 == 0) {
        D_800B40C4 = func_8009D244();
    }
}
