#include "wof.h"

void func_80010AB8(s32 arg0) {
    if (arg0 < 12) {
        if (D_800B9D08[arg0].unk_18 == 0x1111AAFF) {
            D_800B9D08[arg0].unk_04 = D_800B9D08[arg0].unk_08;
            D_800B9D08[arg0].unk_18 = -1;
        }
        if (D_800BA168[arg0].unk_18 == 0x1111AAFF) {
            D_800BA168[arg0].unk_04 = D_800BA168[arg0].unk_08;
            D_800BA168[arg0].unk_18 = -1;
        }
    }
    if (D_800B9E58[arg0].unk_18 == 0x1111AAFF) {
        D_800B9E58[arg0].unk_04 = D_800B9E58[arg0].unk_08;
        D_800B9E58[arg0].unk_18 = -1;
    }
    if (D_800B9FE0[arg0].unk_18 == 0x1111AAFF) {
        D_800B9FE0[arg0].unk_04 = D_800B9FE0[arg0].unk_08;
        D_800B9FE0[arg0].unk_18 = -1;
    }
}
