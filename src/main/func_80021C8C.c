#include "wof.h"

void func_80021C8C(s32 arg0, s32 *arg1, obj_t *arg2, s32 arg3, s32 arg4) {
    s32 unused;  /* NOTE: unused in the original */
    proc_t *task;
    char *sp18;

    if (D_80086D58 != 0) {
        PopMemStack(1);
        func_800A4E58(0);
    }
    D_800B96A4 = 1;
    D_800B81E4 = arg1;
    D_800BCA28 = arg0;
    D_800B998C = gfxInfo[curGfxInfo].frame.unk_0AC00[arg3];
    func_80016B9C(17);
    task = CreatProc(func_80021744, 0x5010000);
    task->unk_30->data80021744.unk_00 = arg2;
    task->unk_30->data80021744.unk_24 = D_80058228[arg0].unk_04;
    task->unk_30->data80021744.unk_10 = arg3;
    task->unk_30->data80021744.unk_20 = arg4;
    D_800BCA0C = PushMemStack();
    D_800B40C4 = 0;
    sp18 = func_80021908(arg0);
    func_8009CEC0(sp18, D_80058228[arg0].unk_0C);
}
