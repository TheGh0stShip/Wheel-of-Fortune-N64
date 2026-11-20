#include "wof.h"

extern s32 D_8004B9FC;

s32 func_80007818(register s32 arg0) {
    u8 value;

    value = arg0;
    if (func_800099B0((s32)&D_8004B9FC, value) != 0) {
        return 1;
    }
    return 0;
}
