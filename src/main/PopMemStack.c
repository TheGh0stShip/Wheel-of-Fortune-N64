#include "wof.h"

void PopMemStack(s32 count) {
    if ((u32)memStackDepth > (u32)count) {
        memStackDepth -= count;
    } else {
        memStackDepth = 0;
    }
    memStackTop = memStackMarks[memStackDepth];
    memStackFree = memStackEnd - memStackTop;
}
