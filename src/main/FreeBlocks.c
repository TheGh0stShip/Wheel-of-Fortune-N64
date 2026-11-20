#include "wof.h"

void FreeBlocks(s32 owner) {
    s32 i;

    for (i = 0; i < 70; i++) {
        if (blockOwners[i] == owner) {
            blockOwners[i] = 0;
        }
    }
}
