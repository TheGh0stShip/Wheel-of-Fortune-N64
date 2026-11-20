#include "wof.h"
#include "rumble.h"


void StartRumble(s32 cont, s32 frames, f32 strength) {
    if (rumbles[cont].unk_00 == 0) {
        return;
    }
    rumbles[cont].unk_0C = frames;
    rumbles[cont].unk_08 = strength;
    rumbles[cont].unk_04 = 0;
}
