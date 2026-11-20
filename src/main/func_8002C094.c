#include "wof.h"

struct n64dk_r12 func_8002C094(proc_t *proc) {
    s32 event;
    s32 i;
    struct n64dk_r12 ret;
    s32 task;

    ret.w[1] = 1;
    ret.w[0] = 0;
    for (;;) {
        event = func_8000ACE8(proc);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            D_800BEE20 = -1;
            for (i = 0; i < 5; i++) {
                D_800B61B0[i] = 0;
            }
            D_800BEE28 = 0;
            D_800BEE4C = 0;
            func_8002B054();
            func_80029440();
            ret.w[1] = 1;
            ret.w[0] = 60 / D_800B96B4;
            func_8000AAB0(proc, 11, 0);
            return ret;
        case 11:
            if (D_800B61A8 < 0) {
                func_80021B04(9, 44);
            } else {
                func_800219B8(9, 44, 180, 20);
            }
            ret.w[1] = 2;
            ret.w[0] = 44;
            return ret;
        case 44:
            for (i = 0; D_8005C394[i] != 0; i++) {
                D_800B966A[D_8005C394[i] - 65] = 32;
                func_80007DAC(D_8005C394[i]);
            }
            task = func_8000A56C(func_80010D3C, 0x1000000);
            ((proc_t *)task)->unk_30->data8002C094.unk_04 = 0;
            ((proc_t *)task)->unk_30->data8002C094.unk_08 = 0;
            ((proc_t *)task)->unk_30->data8002C094.unk_14 = (s32)D_8005C394;
            ret.w[1] = 2;
            ret.w[0] = 6;
            return ret;
        case 6:
            if (D_8005BE00[9].unk_20 != 0) {
                if (func_80007EEC(0) == 1) {
                    func_8000A850(10);
                    func_8000A56C(func_8002BE84, 0x6000000);
                    ret.w[1] = 0;
                    ret.w[0] = 1;
                    return ret;
                }
                D_800BEE20 = func_80002CE0(22);
                func_8002FD50();
                func_8002EBF4();
                task = func_8000A56C(func_8002BA44, 0x5050200);
                func_80027218(task, 0, func_80028554, 0x5050200);
                ret.w[1] = 2;
                ret.w[0] = 10;
                return ret;
            }
            if (D_800B61A8 < 0) {
                func_80021B04(10, 0);
            } else {
                func_800219B8(10, 0, 180, 20);
            }
            func_8002EB40();
            ret.w[1] = 2;
            ret.w[0] = 5;
            return ret;
        case 5:
            if (func_80007818(D_800B61B5) != 0) {
                if (D_8005BE00[9].unk_20 != 0) {
                    func_80002CE0(1);
                    func_8002EB40();
                    ret.w[1] = 2;
                    ret.w[0] = 5;
                    return ret;
                } else {
                    D_800BEE4C++;
                    i = 9;
                }
            } else {
                if (D_800BEE28 >= 3) {
                    func_80002CE0(1);
                    func_8002EB40();
                    ret.w[1] = 2;
                    ret.w[0] = 5;
                    return ret;
                }
                D_800BEE28++;
                i = 6;
            }
            while (i < 10 && D_8005BE00[i].unk_20 != 0) {
                i++;
            }
            D_800B966A[D_800B61B5 - 65] = 32;
            D_8005BE00[i].unk_20 = D_8005BCC8[D_800B61B5 - 65].unk_00;
            D_8005BE00[i].width = D_8005BCC8[D_800B61B5 - 65].width;
            D_8005BE00[i].height = D_8005BCC8[D_800B61B5 - 65].height;
            func_80007DAC(D_800B61B5);
            D_800B61AA[i] = D_800B61B5;
            if (func_80009A74((s32)D_800B61B0) == 4) {
                task = func_8000A56C(func_80010D3C, 0x1000000);
                ((proc_t *)task)->unk_30->data8002C094.unk_04 = 0;
                ((proc_t *)task)->unk_30->data8002C094.unk_08 = 0;
                ((proc_t *)task)->unk_30->data8002C094.unk_14 = (s32)D_800B61B0;
                ret.w[1] = 2;
                ret.w[0] = 6;
            } else {
                func_8002EB40();
                ret.w[1] = 2;
                ret.w[0] = 5;
            }
            return ret;
        case 10:
            if (func_800088E4() == 1) {
                if (D_800BEE20 != -1) {
                    func_80002F58(D_800BEE20);
                }
                task = func_8000A990(0x1020000, -1);
                func_8000AAB0(task, 19, 0);
                func_8000A850(10);
                func_8000A56C(func_8002BE84, 0x6000000);
                ret.w[1] = 0;
                ret.w[0] = 1;
                return ret;
            }
            func_80011F58();
            task = func_8000A990(0x1020000, -1);
            func_8000A4A4(task, 0);
            func_8002EBF4();
            ret.w[1] = 2;
            ret.w[0] = 10;
            return ret;
        case 33:
            if (D_800BEE20 != -1) {
                func_80002F58(D_800BEE20);
            }
            func_80002CE0(1);
            task = func_8000A990(0x1020000, -1);
            func_80011B24();
            func_8000A850(10);
            func_8000A56C(func_8002B904, 0x6000000);
            ret.w[1] = 0;
            ret.w[0] = 1;
            return ret;
        case 34:
            ret.w[1] = 0;
            ret.w[0] = 1;
            return ret;
        }
    }
    return ret;
}
