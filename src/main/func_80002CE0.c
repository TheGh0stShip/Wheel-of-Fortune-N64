#include "wof.h"


s32 func_80002CE0(s32 arg0) {
    f32 sp10;
    s32 pad0;
    s32 slot;

    if (arg0 >= D_800A5090->soundCount) {
        arg0 = 0;
    }
    D_800A5098 = D_800A5090->soundArray[arg0];
    slot = func_80002700();
    if (slot == -1) {
        return -1;
    }
    D_800A509C[slot] = alSndpAllocate(D_8004B718, D_800A5098);
    if (D_800A509C[slot] == -1) {
        return -1;
    }
    alSndpSetSound(D_8004B718, D_800A509C[slot]);
    switch (D_800A5098->keyMap->detune) {
    case 0:
        sp10 = 0.18728799f;
        break;
    case 1:
        sp10 = 0.23596825f;
        break;
    case 2:
        sp10 = 0.2648662f;
        break;
    case 3:
        sp10 = 0.31497958f;
        break;
    case 4:
        sp10 = 0.35355556f;
        break;
    case 5:
        sp10 = 0.3968254f;
        break;
    case 6:
        sp10 = 0.420449f;
        break;
    case 7:
        sp10 = 0.5f;
        break;
    case 8:
        sp10 = 0.5946032f;
        break;
    case 9:
        sp10 = 0.6674195f;
        break;
    case 10:
        sp10 = 1.0f;
        break;
    }
    alSndpSetPitch(D_8004B718, sp10);
    alSndpPlay(D_8004B718);
    return slot;
}
