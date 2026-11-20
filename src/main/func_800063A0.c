#include "wof.h"

typedef s32 M2C_UNK;
M2C_UNK osCreatePiManager(); /* extern */
M2C_UNK osCreateThread(); /* extern */
M2C_UNK osSetThreadPri();           /* extern */
M2C_UNK osStartThread();                   /* extern */
extern s32 D_8004B83C;
extern M2C_UNK D_800AD5F0;
extern M2C_UNK D_800AD950;
extern M2C_UNK D_800AFB00;
extern M2C_UNK D_800AFE20;
extern M2C_UNK D_800BED88;
extern M2C_UNK func_800065D4;
extern M2C_UNK func_800067D8;

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
