#include "wof.h"

void InitMemStack(void) {
    memStackBase = memStart;
    memStackEnd = memEnd;
    memStackFree = memStackEnd - memStackBase;
    memStackDepth = 0;
    memStackTop = memStackBase;
}
