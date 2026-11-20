#include "wof.h"

void func_80023200(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        D_800B9990[i].unk_014 = D_800584C8[i].sel;
        func_80024D60(i);
    }
}
