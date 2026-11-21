// AllocMem.c -- take aligned memory from the memory stack

#include "wof.h"

/*
=====================
AllocMem

Aligns the memory stack to 8 bytes and takes size bytes from it.
=====================
*/
void *AllocMem(s32 size) {
    AlignMemStack(8);
    return mem_stack(size);
}
