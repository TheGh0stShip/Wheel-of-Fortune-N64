#include "wof.h"

void func_800894F8(void) {
    s32 i;

    for (i = -2048; i < 0x1000; i++) {
        if (i <= 0) {
            D_800FC098[i] = 0;
        } else if (i >= 255) {
            D_800FC098[i] = 255;
        } else {
            D_800FC098[i] = i;
        }
    }
}
