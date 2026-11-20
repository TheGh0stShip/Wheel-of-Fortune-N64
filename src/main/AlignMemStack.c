#include "wof.h"

void AlignMemStack(s32 align) {
    s32 rem;

    rem = memStackTop & (align - 1);
    if (rem != 0) {
        memStackTop = memStackTop + (align - rem);
        memStackFree = memStackFree - (align - rem);
    }
}
