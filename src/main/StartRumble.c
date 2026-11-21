#include "wof.h"
#include "rumble.h"


/*
=====================
StartRumble

Rumbles a controller's pak for some frames at some strength.
=====================
*/
void StartRumble(s32 cont, s32 frames, f32 strength) {
    if (rumbles[cont].present == 0) {
        return;
    }
    rumbles[cont].frames = frames;
    rumbles[cont].strength = strength;
    rumbles[cont].level = 0;
}
