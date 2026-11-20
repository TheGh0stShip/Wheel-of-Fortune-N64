#include "wof.h"


void *mem_stack(s32 size) {
    s32 result;

    if ((u32)size > (u32)memStackFree) {
        func_80009F38("mem_stack: OUT OF MEMMORY!!!");
        return 0;
    }
    result = memStackTop;
    memStackTop = memStackTop + size;
    memStackFree = memStackFree - size;
    return (void *)result;
}
