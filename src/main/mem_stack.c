// mem_stack.c -- takes bytes from the top of the memory stack; there is no freeing but PopMemStack

#include "wof.h"


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
