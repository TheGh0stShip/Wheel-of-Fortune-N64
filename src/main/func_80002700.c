#include "wof.h"

s32 func_80002700(void) {
    s32 i;

    D_800BC6F8 = 0;
    for (i = 31; i > 0; i--) {
        if (D_800A509C[i] != -1) {
            alSndpSetSound(D_8004B718, D_800A509C[i]);
            if ((D_800B81F0[i] = alSndpGetState(D_8004B718)) == 0) {
                alSndpDeallocate(D_8004B718, D_800A509C[i]);
                D_800A509C[i] = -1;
            } else {
                D_800BC6F8++;
            }
        }
    }
    i = 0;
    while (i < D_800A5090->soundCount) {
        if (D_800A509C[i] == -1) {
            return i;
        }
        i++;
    }
    return -1;
}
