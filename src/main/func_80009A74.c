#include "wof.h"

s32 func_80009A74(u8 *arg0) {
    s32 len;

    len = 0;
    while (arg0[len] != 0) {
        len++;
    }
    return len;
}
