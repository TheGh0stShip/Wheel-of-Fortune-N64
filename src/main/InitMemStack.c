#include "wof.h"

/*
=====================
InitMemStack

Sets the memory stack to the free memory; named after mem_stack.
=====================
*/
void InitMemStack(void) {
    memStackBase = memStart;
    memStackEnd = memEnd;
    memStackFree = memStackEnd - memStackBase;
    memStackDepth = 0;
    memStackTop = memStackBase;
}
