// PushMemStack.c -- saves the top of the memory stack, up to 10 deep

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
