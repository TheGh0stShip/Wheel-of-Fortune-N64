#include "wof.h"

extern f32 D_800007CC;
extern s32 D_800BEDA8;
extern s32 D_800BEDF8;
s32 func_80009C98(s32 arg0);

void func_80009108(f32 arg0) {
    s32 angle;

    if (arg0 == D_800007CC) {
        D_800BEDA8 += func_80009C98(24);
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
