#include "wof.h"

void func_800325D0(s32 arg0, s32 arg1);

void func_80032B80(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        func_800325D0(1, i);
    }
}
