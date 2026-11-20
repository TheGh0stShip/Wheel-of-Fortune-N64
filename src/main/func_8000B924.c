#include "wof.h"

void *func_8000B924(s32 size) {
    AlignMemStack(8);
    return mem_stack(size);
}
