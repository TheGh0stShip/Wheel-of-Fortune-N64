// SetLightColor.c -- gSPLightColor on one of the six lights

#include "wof.h"

/*
=====================
SetLightColor

GSPLightColor on one of the six lights.
=====================
*/
void SetLightColor(s32 light) {
    switch (light) {
    case 1:
        gSPLightColor(glistp++, LIGHT_1, 0x505050FF);
        return;
    case 2:
        gSPLightColor(glistp++, LIGHT_2, 0x8C8C8CFF);
        return;
    case 3:
        gSPLightColor(glistp++, LIGHT_3, 0x8C8C8CFF);
        return;
    case 4:
        gSPLightColor(glistp++, LIGHT_4, 0x8C8C8CFF);
        return;
    case 5:
        gSPLightColor(glistp++, LIGHT_5, 0x8C8C8CFF);
        return;
    case 6:
        gSPLightColor(glistp++, LIGHT_6, 0x141414FF);
        return;
    }
}
