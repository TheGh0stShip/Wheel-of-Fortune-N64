#include "wof.h"

extern s32 D_800B966A;

void func_8001A628(s32 arg0) {
    s32 found;
    u8 *p;

    p = (u8 *)arg0;
    while (func_80009A74((s32)p) > 0) {
        found = func_800099B0((s32)&D_800B966A, *p);
        if (found == 0) {
            func_80009900((s32)p, (s32)(p + 1));
        } else {
            p++;
        }
    }
}
