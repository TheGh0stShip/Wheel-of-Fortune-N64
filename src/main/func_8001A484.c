#include "wof.h"

void func_8001A484(void) {
    s32 unused;  /* NOTE: unused in the original */
    s32 unused2;  /* NOTE: unused in the original */
    s32 i;

    func_8001A5D0();
    for (i = 0; i < 3; i++) {
        if (D_800BCD54 == 3) {
            func_8001D320(i);
        } else if (D_800B9990[i].unk_014 < 4) {
            func_8001A424(i);
        } else {
            func_8001D3CC(i);
        }
        D_800B39A0[i][0] = 0;
        D_800B39A0[i][1] = 0;
    }
    if (D_800BCD54 == 3) {
        func_80017C00(17, 0);
        return;
    }
    func_80017C00(3, 0);
}
