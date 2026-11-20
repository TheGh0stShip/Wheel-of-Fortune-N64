#include "wof.h"

void *func_8000A31C(s32 arg0) {
    s32 i;

    for (i = 0; i < 70; i++) {
        if (D_800BA5E0[i] == 0) {
            D_800BA5E0[i] = arg0;
            return D_800B6BF8[i];
        }
    }
    func_80009F38("AllocBlock: Out of Blocks.\n");
    return 0;
}
