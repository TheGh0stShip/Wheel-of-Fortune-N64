#include "wof.h"

void func_80002B34(void) {
    s32 i;

    for (i = 31; i > 0; i--) {
        if (D_800A509C[i] != -1) {
            func_80049FA8(D_8004B718, D_800A509C[i]);
            if ((D_800B81F0[i] = func_8003CE38(D_8004B718)) == 0) {
                func_80049FC8(D_8004B718);
            }
        }
    }
}
