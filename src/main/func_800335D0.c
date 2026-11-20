#include "wof.h"

void func_800335D0(void) {
    if (D_800B40C4 == 0) {
        return;
    }
    ResetMotors();
    D_800BA2C0 = (s32)(osGetTime() / osClockRate);
    D_800BED98 = gameMode;
    gameMode = 6;
    MakeObj(0, 0, func_80028B1C, 0x5020000);
    PauseSounds();
}
