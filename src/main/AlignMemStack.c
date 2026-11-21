#include "wof.h"

/*
=====================
AlignMemStack

Rounds the top of the memory stack up to a power of two.
=====================
*/
void AlignMemStack(s32 align) {
    s32 rem;

    rem = memStackTop & (align - 1);
    if (rem != 0) {
        memStackTop = memStackTop + (align - rem);
        memStackFree = memStackFree - (align - rem);
    }
}
