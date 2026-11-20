#include "wof.h"

void func_80006328(void) {
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    osInitialize();
    osCreateThread(&D_800AD7A0, 1, func_800063A0, D_800BA5D4, &D_800AFB00, 10);
    osStartThread(&D_800AD7A0);
}
