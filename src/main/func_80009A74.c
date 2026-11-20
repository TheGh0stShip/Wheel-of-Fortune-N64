#include "wof.h"

s32 func_80009A74(s32 arg0) {
    s32 len;

    len = 0;
    while (((u8 *)arg0)[len] != 0) {
        len++;
    }
    return len;
}
