#include "wof.h"

void func_800030E8(s32 arg0, f32 arg1) {
    alSndpSetSound(D_8004B718, D_800A509C[arg0]);
    alSndpSetPitch(D_8004B718, arg1);
}
