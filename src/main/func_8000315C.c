#include "wof.h"

void func_8000315C(void) {
    s32 i;

    for (i = 31; i >= 0; i--) {
        if (D_800A509C[i] != -1) {
            alSndpSetSound(D_8004B718, D_800A509C[i]);
            alSndpStop(D_8004B718);
        }
    }
    alCSPStop(D_800BED90[0]);
}
