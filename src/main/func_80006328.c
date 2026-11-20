#include "wof.h"

void func_80006328(void) {
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    osInitialize();
    osCreateThread(&D_800AD7A0, 1, func_800063A0, (void *)D_800BA5D4, D_800ADB00 + 0x2000 / sizeof(u64), 10);
    osStartThread(&D_800AD7A0);
}
