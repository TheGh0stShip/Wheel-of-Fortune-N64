#include "wof.h"

void func_80010AB8(s32 arg0) {
    if (arg0 < 12) {
        if (D_800B9D0C[arg0].unk_14 == 0x1111AAFF) {
            D_800B9D0C[arg0].unk_00 = D_800B9D0C[arg0].unk_04;
            D_800B9D0C[arg0].unk_14 = -1;
        }
        if (D_800BA16C[arg0].unk_14 == 0x1111AAFF) {
            D_800BA16C[arg0].unk_00 = D_800BA16C[arg0].unk_04;
            D_800BA16C[arg0].unk_14 = -1;
        }
    }
    if (D_800B9E5C[arg0].unk_14 == 0x1111AAFF) {
        D_800B9E5C[arg0].unk_00 = D_800B9E5C[arg0].unk_04;
        D_800B9E5C[arg0].unk_14 = -1;
    }
    if (D_800B9FE4[arg0].unk_14 == 0x1111AAFF) {
        D_800B9FE4[arg0].unk_00 = D_800B9FE4[arg0].unk_04;
        D_800B9FE4[arg0].unk_14 = -1;
    }
}
