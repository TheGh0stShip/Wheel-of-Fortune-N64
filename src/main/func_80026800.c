#include "wof.h"

void func_80026800(void) {
    s32 i;
    s32 j;
    s32 clashes;
    s32 obj;

    obj = func_8000A56C(func_80025150, 0x5000000);
    func_80027218(obj, 0, func_80022218, 0x5000000);
    func_800258BC();
    for (i = 0; i < 3; i++) {
        if (D_800B9990[i].unk_014 == 4) {
            do {
                clashes = 0;
                for (j = 0; j < 3; j++) {
                    if (i != j) {
                        if (D_800B9990[i].unk_018 == D_800B9990[j].unk_018) {
                            clashes++;
                        }
                    }
                }
                if (clashes != 0) {
                    D_800B9990[i].unk_018++;
                    if (D_800B9990[i].unk_018 >= 6) {
                        D_800B9990[i].unk_018 = 0;
                    }
                }
            } while (clashes > 0);
        }
    }
    i = 0;
    while (i < 3) {
        func_800323C4(D_800B9990[i].unk_018, i, D_8005A474[i].unk_00, D_8005A474[i].unk_04, D_8005A474[i].unk_08);
        switch (D_800584C8[i].sel) {
        case 0:
            D_80058B28[i * 3 + 2].unk_20 = (s32)D_01158068;
            D_80058B28[i * 3 + 2].unk_24 = (s32)D_01158068;
            break;
        case 1:
            D_80058B28[i * 3 + 2].unk_20 = (s32)D_01158868;
            D_80058B28[i * 3 + 2].unk_24 = (s32)D_01158868;
            break;
        case 2:
            D_80058B28[i * 3 + 2].unk_20 = (s32)D_01159068;
            D_80058B28[i * 3 + 2].unk_24 = (s32)D_01159068;
            break;
        case 3:
            D_80058B28[i * 3 + 2].unk_20 = (s32)D_01159868;
            D_80058B28[i * 3 + 2].unk_24 = (s32)D_01159868;
            break;
        case 4:
            D_80058B28[i * 3 + 2].unk_20 = (s32)D_01157868;
            D_80058B28[i * 3 + 2].unk_24 = (s32)D_01157868;
            break;
        }
        i++;
    }
}
