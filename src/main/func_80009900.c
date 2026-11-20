#include "wof.h"

u8 *func_80009900(u8 *arg0, u8 *arg1) {
    s32 i;

    i = 0;
    while (arg1[i] != 0) {
        arg0[i] = arg1[i];
        i++;
    }
    arg0[i] = arg1[i];
    return arg0;
}
