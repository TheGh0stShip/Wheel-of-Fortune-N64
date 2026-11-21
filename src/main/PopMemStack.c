// PopMemStack.c -- drops a number of saved tops and goes back to the one under them

#include "wof.h"

/*
=====================
PopMemStack

Drops a number of saved tops and goes back to the one under them.
=====================
*/
void PopMemStack(s32 count) {
    if ((u32)memStackDepth > (u32)count) {
        memStackDepth -= count;
    } else {
        memStackDepth = 0;
    }
    memStackTop = memStackMarks[memStackDepth];
    memStackFree = memStackEnd - memStackTop;
}
