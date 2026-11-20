#include "wof.h"

s32 PushMemStack(void) {
    if ((u32)memStackDepth < 10) {
        memStackMarks[memStackDepth++] = memStackTop;
        return 1;
    } else {
        return 0;
    }
}
