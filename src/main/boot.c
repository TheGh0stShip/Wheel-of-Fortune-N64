// boot.c -- guess: boot of the SDK demos. Starts the OS and the idle thread

#include "wof.h"

/*
=====================
boot

guess: boot of the SDK demos. Starts the OS and the idle thread.
=====================
*/
void boot(void) {
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    osInitialize();
    osCreateThread(&idleThread, 1, idle, (void *)D_800BA5D4, idleThreadStack + 0x2000 / sizeof(u64), 10);
    osStartThread(&idleThread);
}
