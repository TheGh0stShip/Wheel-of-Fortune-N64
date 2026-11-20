#include "wof.h"


void func_800087F8(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 14; j++) {
            D_800B95AD[i][j] = D_800B9559[i][j];
        }
    }
}
