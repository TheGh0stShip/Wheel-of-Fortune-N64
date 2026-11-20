#include "wof.h"

void func_8000BB10(void) {
    OSMesg sp10;

    if (D_80057800 == 0) {
        func_8000BAA8();
    }
    osRecvMesg(&D_800BA5B0, &sp10, 1);
}
