#include "wof.h"

void func_800028E4(void) {
    s32 i;

    D_800BC6F8 = 0;
    for (i = 31; i > 0; i--) {
        if (D_800A509C[i] != -1) {
            func_80049FA8(D_8004B718, D_800A509C[i]);
            switch (D_800B81F0[i] = func_8003CE38(D_8004B718)) {
            case 0:
            case 2:
                func_80049F58(D_8004B718, D_800A509C[i]);
                D_800A509C[i] = -1;
                break;
            default:
                D_800BC6F8++;
            }
        }
    }
    i = 31;
    for (; i > 0; i--) {
        if (D_800A509C[i] != -1) {
            func_80049FA8(D_8004B718, D_800A509C[i]);
            if ((D_800B81F0[i] = func_8003CE38(D_8004B718)) == 1) {
                func_8003CDE8(D_8004B718);
            }
        }
    }
}
