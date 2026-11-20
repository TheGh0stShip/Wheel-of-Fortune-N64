#include "wof.h"

void func_800063A0(s32 arg0) {
    osCreatePiManager(0x96, &D_800AFE20, &D_800AFB00, 0xC8);
    osCreateThread(&D_800AD5F0, 0xA, &func_800065D4, arg0, &D_800BED88, 0xA);
    osCreateThread(&D_800AD950, 0xB, &func_800067D8, arg0, &D_800AD5F0, 8);
    if (D_8004B83C == 0) {
        osStartThread(&D_800AD5F0);
    }
    osSetThreadPri(0, 0);
loop_3:
    goto loop_3;
}
