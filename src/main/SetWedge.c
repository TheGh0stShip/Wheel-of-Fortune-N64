#include "wof.h"


/*
=====================
SetWedge

The wedge the wheel stopped on, from its angle (or a random one for -1)
=====================
*/
void SetWedge(f32 degrees) {
    s32 angle;

    if (degrees == -1.0f) {
        curWedge += Random(24);
    } else {
        angle = (s32)degrees;
        if (angle < 0) {
            angle *= -1;
        }
        angle %= 360;
        curWedge = angle / 15;
        wedgeThird = angle / 5;
    }
    if (curWedge >= 24) {
        curWedge %= 24;
    }
}
