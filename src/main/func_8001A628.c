#include "wof.h"


void func_8001A628(u8 *arg0) {
    u8 *found;
    u8 *p;

    p = arg0;
    while (StrLen(p) > 0) {
        found = StrChr(D_800B966A, *p);
        if (found == 0) {
            StrCopy(p, p + 1);
        } else {
            p++;
        }
    }
}
