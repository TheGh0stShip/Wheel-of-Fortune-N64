#include "wof.h"


void func_80009108(f32 arg0) {
    s32 angle;

    if (arg0 == -1.0f) {
        D_800BEDA8 += Random(24);
    } else {
        angle = (s32)arg0;
        if (angle < 0) {
            angle *= -1;
        }
        angle %= 360;
        D_800BEDA8 = angle / 15;
        D_800BEDF8 = angle / 5;
    }
    if (D_800BEDA8 >= 24) {
        D_800BEDA8 %= 24;
    }
}
