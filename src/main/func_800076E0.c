#include "wof.h"

s32 func_800076E0(register s32 arg0) {
    u8 ch;
    s32 i;
    s32 count;
    u8 *p;

    ch = arg0;
    p = StrChr(D_800B966A, ch);
    if (p == 0) {
        return -1;
    }
    count = 0;
    for (i = 0; i < 4; i++) {
        p = D_800B9601[i];
        while (p != 0) {
            p = StrChr(p, ch);
            if (p != 0) {
                count++;
                p++;
            }
        }
    }
    return count;
}
