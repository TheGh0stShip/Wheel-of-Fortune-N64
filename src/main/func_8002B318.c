#include "wof.h"


struct n64dk_r12 func_8002B318(proc_t *proc) {
    s32 event;
    s32 i;
    struct n64dk_r12 ret;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    ret.w[1] = 1;
    ret.w[0] = 0;
    while ((event = func_8000ACE8(proc)) != 0) {
        switch (event) {
        case 8:
            i = 0;
            for (;;) {
                if (i >= 22) {
                    break;
                }
                D_8005B710[i].unk_20 = 0;
                D_8005B710[i].unk_24 = 0;
                i++;
            }
            func_80005258();
            func_80027218(0, 0, func_80028064, 0x5050000);
            proc->unk_30->data8002B318.step = 0;
            D_800BCD54 = 8;
            func_8000B6FC(0x5050100, -1);
            func_8000AE70(0xA000400, -1, 1);
            func_8000B6FC(0xA030000, -1);
            func_80002CE0(21);
            break;
        case 46:
            func_8000315C();
            ret.w[1] = 1;
            ret.w[0] = 2;
            func_8000B6FC(0x1000000, 0xFF000000);
            func_8000B6FC(0xA000000, 0xFF000000);
            func_8000B6FC(0x4000000, 0xFF000000);
            func_8000AAB0(proc, 35, 0);
            return ret;
        case 35:
            func_8000ADEC(proc);
            func_8000AF00();
            func_80021E28();
            func_8000E794();
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        }
    }
    if (proc->unk_30->data8002B318.step >= 22) {
        func_8000AAB0(proc, 46, 0);
        return ret;
    }
    func_800161A8();
    func_80006E54(0, D_8005C1E8[proc->unk_30->data8002B318.step]);
    if (D_8005C33C[proc->unk_30->data8002B318.step] != 0) {
        func_80009900((s32)&D_800B9544, D_8005C33C[proc->unk_30->data8002B318.step]);
        func_80029440();
    }
    func_80011B24();
    proc->unk_30->data8002B318.step++;
    ret.w[0] = 65 / D_800B96B4;
    return ret;
}
