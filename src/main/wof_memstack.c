// wof_memstack.c -- the memory stack: setting it up, taking bytes from it, aligning it
//
// InitMemStack, mem_stack and AlignMemStack each end off an 8-byte boundary with the next function
// right after, which happens only inside an object. Whether FreeObjClass before it and PushMemStack
// after it are this object's the text does not say.

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

/*
=====================
mem_stack

Takes bytes from the top of the memory stack; there is no freeing but PopMemStack.
=====================
*/
void *mem_stack(s32 size) {
    s32 result;

    if ((u32)size > (u32)memStackFree) {
        FatalError("mem_stack: OUT OF MEMMORY!!!");
        return 0;
    }
    result = memStackTop;
    memStackTop = memStackTop + size;
    memStackFree = memStackFree - size;
    return (void *)result;
}

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
