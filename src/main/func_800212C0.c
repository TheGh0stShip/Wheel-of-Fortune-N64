#include "wof.h"

void func_800212C0(s32 arg0) {
    s32 diff;
    s32 pad0;
    s32 pad1[6];
    s32 pad2;
    s32 base;

    base = 0x2000000;
    diff = osVirtualToPhysical(D_800BEF08[D_800B61A0].frame.unk_19C00);
    diff = diff - osVirtualToPhysical(&D_800BEF08[D_800B61A0].frame);
    (*(obj_t **)((proc_t *)arg0)->unk_30)->unk_44 = base + diff;
    if (D_800B40C4 == 0) {
        D_800B40C4 = func_8009D244();
    }
}
