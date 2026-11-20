#include "wof.h"

u8 *func_80009804(u8 *arg0, u8 *arg1) {
    s32 i;
    s32 j;

    i = 0;
    while (arg0[i] != 0) {
        i++;
    }
    j = 0;
    while (arg1[j] != 0) {
        arg0[i] = arg1[j];
        i++;
        j++;
    }
    arg0[i] = arg1[j];
    return arg0;
}
