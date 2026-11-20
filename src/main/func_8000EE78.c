#include "wof.h"


void func_8000EE78(void) {
    s32 unused[4];  /* NOTE: unused in the original; guess: its type, the frame shows at most 16 bytes */

    D_800BCD54 = 3;
    D_800B8298 = 0.65f;
    do {
    } while (D_800BEDE4 != 0 && D_800B96AC < 100);
    func_800174DC();
    func_8002FE70();
    func_80006B28();
    func_80016310();
    func_80032BF0();
    func_8001A484();
    func_8002EC60();
    func_8000A56C(func_8000EB40, 0x9000000);
    func_80015848(0, 0, func_800287A4, 0x5000000);
    func_80033CBC();
}
