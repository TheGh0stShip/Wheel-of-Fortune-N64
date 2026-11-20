#include "wof.h"

void func_8000BBA8(void) {
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    do {
    } while (D_800BEDE4 != 0 && D_800B96AC < 100);
    D_800BCD54 = 2;
    func_800339E8();
    func_800174DC();
    func_8002FE2C();
    func_80006B28();
    func_80016310();
    func_80032BF0();
    func_8001A484();
    func_8002EC60();
    func_80033CBC();
}
