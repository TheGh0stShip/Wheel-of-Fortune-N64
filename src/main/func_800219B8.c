#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u8 unk_0C[0x4];
} Board;

extern Board D_8005822C[];

void func_800219B8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    proc_t *obj;
    s32 sp1C;

    if (D_80086D58 != 0) {
        func_8000B9FC(1);
        func_800A4E58(0);
    }
    D_800BCA28 = arg0;
    D_800B96A4 = 0;
    obj = (proc_t *)func_8000A56C((s32)func_80021548, 0x5010000);
    ((data80021548_t *)obj->unk_30)->unk_00 = func_800211E4((s32)obj, &D_80058488, arg2, arg3, arg0);
    ((data80021548_t *)obj->unk_30)->unk_24 = D_8005822C[arg0].unk_00;
    ((data80021548_t *)obj->unk_30)->unk_20 = arg1;
    D_800BCA0C = func_8000B978();
    D_800B40C4 = 0;
    sp1C = func_80021908(arg0);
    func_8009CEC0(sp1C, D_8005822C[arg0].unk_08);
}
