#include "wof.h"

void func_80002F58(s32 arg0) {
    alSndpSetSound(D_8004B718, D_800A509C[arg0]);
    alSndpStop(D_8004B718);
    alSndpDeallocate(D_8004B718, D_800A509C[arg0]);
    D_800A509C[arg0] = -1;
}
