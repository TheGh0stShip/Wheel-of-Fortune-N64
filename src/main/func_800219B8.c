#include "wof.h"

void func_800219B8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    proc_t *task;
    char *sp1C;

    if (D_80086D58 != 0) {
        PopMemStack(1);
        func_800A4E58(0);
    }
    D_800BCA28 = arg0;
    D_800B96A4 = 0;
    task = CreatProc(func_80021548, 0x5010000);
    task->data->data80021548.unk_00 = func_800211E4(task, D_80058488, arg2, arg3, arg0);
    task->data->data80021548.unk_24 = D_80058228[arg0].unk_04;
    task->data->data80021548.unk_20 = arg1;
    D_800BCA0C = PushMemStack();
    D_800B40C4 = 0;
    sp1C = func_80021908(arg0);
    func_8009CEC0(sp1C, D_80058228[arg0].unk_0C);
}
