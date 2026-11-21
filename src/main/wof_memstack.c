// wof_memstack.c -- the memory stack: setting it up, taking bytes from it, aligning it, saving its top
// and going back to a saved one
//
// InitMemStack, mem_stack, AlignMemStack and PushMemStack each end off an 8-byte boundary with the next
// function right after, which happens only inside an object; a 4-byte gap ends the text after
// PopMemStack. The join after AllocMem rests on the RCS premise (every object from 0x8000BAA8 on opens
// its read-only data with an RCS run, which the project accepts): no run lies where an object starting
// at PushMemStack would need one. guess: the boundary before InitMemStack (see wof_obj.c), where the
// zero word before 0x80000AA0 opens mem_stack's read-only data.

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
