#include "wof.h"

void func_80006328(void) {
    s8 pad0;

    osInitialize();
    osCreateThread(&D_800AD7A0, 1, func_800063A0, D_800BA5D4, &D_800AFB00, 10);
    osStartThread(&D_800AD7A0);
}
