#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 pad4[0x4];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u8 padC[0x4];
} Info;

extern Info D_8005822C[];
void func_80021C8C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 pad0;
    proc_t *task;
    s32 sp18;

    if (D_80086D58 != 0) {
        func_8000B9FC(1);
        func_800A4E58(0);
    }
    D_800B96A4 = 1;
    D_800B81E4 = arg1;
    D_800BCA28 = arg0;
    D_800B998C = (s32)&D_800BEF08[D_800B61A0].frame.unk_0AC00[arg3];
    func_80016B9C(17);
    task = (proc_t *)func_8000A56C((s32)func_80021744, 0x5010000);
    ((data80021744_t *)task->unk_30)->unk_00 = arg2;
    ((data80021744_t *)task->unk_30)->unk_24 = D_8005822C[arg0].unk_00;
    ((data80021744_t *)task->unk_30)->unk_10 = arg3;
    ((data80021744_t *)task->unk_30)->unk_20 = arg4;
    D_800BCA0C = func_8000B978();
    D_800B40C4 = 0;
    sp18 = func_80021908(arg0);
    func_8009CEC0(sp18, D_8005822C[arg0].unk_08);
}
