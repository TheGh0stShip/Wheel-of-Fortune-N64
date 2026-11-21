// FreeBlocks.c -- frees the data blocks a proc owns

#include "wof.h"

/*
=====================
FreeBlocks

Frees the data blocks a proc owns.
=====================
*/
void FreeBlocks(s32 owner) {
    s32 i;

    for (i = 0; i < 70; i++) {
        if (blockOwners[i] == owner) {
            blockOwners[i] = 0;
        }
    }
}
