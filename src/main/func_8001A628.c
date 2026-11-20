#include "wof.h"


void func_8001A628(u8 *arg0) {
    u8 *found;
    u8 *p;

    p = arg0;
    while (func_80009A74(p) > 0) {
        found = func_800099B0(D_800B966A, *p);
        if (found == 0) {
            func_80009900(p, p + 1);
        } else {
            p++;
        }
    }
}
