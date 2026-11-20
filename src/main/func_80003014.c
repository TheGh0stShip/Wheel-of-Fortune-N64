#include "wof.h"

void func_80003014(s32 arg0, register s32 arg1, register s32 arg2, register s32 arg3) {
    u8 sp10;
    u8 sp11;
    s16 sp12;

    sp10 = arg1;
    sp11 = arg2;
    sp12 = arg3;
    alSndpSetSound(D_8004B718, D_800A509C[arg0]);
    alSndpSetFXMix(D_8004B718, sp10);
    alSndpSetPan(D_8004B718, sp11);
    alSndpSetVol(D_8004B718, sp12);
}
