#include "wof.h"

u8 *func_80009748(u8 *arg0, u8 *arg1, s32 arg2) {
    s32 i;
    s32 j;

    i = 0;
    j = 0;
    while (i < arg2) {
        arg0[i] = arg1[j];
        if (arg1[j] != 0) {
            j++;
        }
        i++;
    }
    return arg0;
}
