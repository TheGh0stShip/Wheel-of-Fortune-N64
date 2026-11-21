#include "wof.h"

void StartCelebration(void) {
    D_800B81E4 = &D_8006DDC4;
    PlayMovie(0x16, 0, 0x28, 0xF);
    CreatProc(ConfettiBurstProc, 0x05030000);
}
