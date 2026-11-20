#include "wof.h"

typedef s32 M2C_UNK;
extern s32 D_80057800;
extern M2C_UNK D_800BA5B0;

void func_8000BB10(void) {
    M2C_UNK sp10;

    if (D_80057800 == 0) {
        func_8000BAA8();
    }
    osRecvMesg(&D_800BA5B0, &sp10, 1);
}
