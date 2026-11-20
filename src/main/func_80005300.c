#include "wof.h"

void func_80005300(s32 arg0) {
    switch (arg0) {
    case 1:
        gSPLightColor(D_800B81E8++, LIGHT_1, 0x505050FF);
        return;
    case 2:
        gSPLightColor(D_800B81E8++, LIGHT_2, 0x8C8C8CFF);
        return;
    case 3:
        gSPLightColor(D_800B81E8++, LIGHT_3, 0x8C8C8CFF);
        return;
    case 4:
        gSPLightColor(D_800B81E8++, LIGHT_4, 0x8C8C8CFF);
        return;
    case 5:
        gSPLightColor(D_800B81E8++, LIGHT_5, 0x8C8C8CFF);
        return;
    case 6:
        gSPLightColor(D_800B81E8++, LIGHT_6, 0x141414FF);
        return;
    }
}
