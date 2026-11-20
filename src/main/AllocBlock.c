#include "wof.h"

void *AllocBlock(s32 owner) {
    s32 i;

    for (i = 0; i < 70; i++) {
        if (blockOwners[i] == 0) {
            blockOwners[i] = owner;
            return blocks[i];
        }
    }
    func_80009F38("AllocBlock: Out of Blocks.\n");
    return 0;
}
