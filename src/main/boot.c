#include "wof.h"

void boot(void) {
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    osInitialize();
    osCreateThread(&idleThread, 1, idle, (void *)D_800BA5D4, idleThreadStack + 0x2000 / sizeof(u64), 10);
    osStartThread(&idleThread);
}
