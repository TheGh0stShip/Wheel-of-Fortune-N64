#include "wof.h"

void func_80002B34(void) {
    s32 i;

    for (i = 31; i > 0; i--) {
        if (D_800A509C[i] != -1) {
            alSndpSetSound(D_8004B718, D_800A509C[i]);
            if ((D_800B81F0[i] = alSndpGetState(D_8004B718)) == 0) {
                alSndpPlay(D_8004B718);
            }
        }
    }
}
