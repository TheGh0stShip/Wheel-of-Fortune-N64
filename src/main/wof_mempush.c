// wof_mempush.c -- saving the top of the memory stack and going back to a saved one
//
// PushMemStack ends off an 8-byte boundary with PopMemStack right after, which happens only inside an
// object; a 4-byte gap ends the text after PopMemStack. Whether AllocMem before it is this object's the
// text does not say.

#include "wof.h"

/*
=====================
PushMemStack

Saves the top of the memory stack, up to 10 deep.
=====================
*/
s32 PushMemStack(void) {
    if ((u32)memStackDepth < 10) {
        memStackMarks[memStackDepth++] = memStackTop;
        return 1;
    } else {
        return 0;
    }
}

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
