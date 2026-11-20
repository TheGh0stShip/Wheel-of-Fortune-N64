#include "wof.h"

void func_800063A0(void *arg) {
    osCreatePiManager(OS_PRIORITY_PIMGR, &D_800AFE20, D_800AFB00, 200);
    osCreateThread(&D_800AD5F0, 10, func_800065D4, arg, D_800BCD88 + 0x2000 / sizeof(u64), 10);
    osCreateThread(&D_800AD950, 11, func_800067D8, arg, D_800AB5F0 + 0x2000 / sizeof(u64), 8);
    if (D_8004B83C == 0) {
        osStartThread(&D_800AD5F0);
    }
    osSetThreadPri(0, 0);
loop_3:
    goto loop_3;
}
