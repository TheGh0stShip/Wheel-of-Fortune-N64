#include "wof.h"

typedef struct {
    /* 0x00 */ obj_t *unk_00;
    /* 0x04 */ u8 unk_04[0xC];
    /* 0x10 */ s32 unk_10;
} Ref;

void func_800213CC(proc_t *arg0) {
    s32 sp10;
    s32 pad0;
    s32 pad1[6];
    s32 pad2;
    s32 sp34;

    sp34 = 0x2000000;
    sp10 = osVirtualToPhysical(D_800BEF08[D_800B61A0].frame.unk_0AC00[((Ref *)arg0->unk_30)->unk_10]);
    sp10 = sp10 - osVirtualToPhysical(&D_800BEF08[D_800B61A0].frame);
    ((Ref *)arg0->unk_30)->unk_00->unk_44 = sp34 + sp10;
    D_800B998C = D_800BEF08[D_800B61A0].frame.unk_0AC00[((Ref *)arg0->unk_30)->unk_10];
    if (D_800B40C4 == 0) {
        D_800B40C4 = func_8009D244();
    }
}
