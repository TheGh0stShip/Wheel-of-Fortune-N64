#include "wof.h"

void func_8000A408(s32 arg0) {
    s32 i;

    for (i = 0; i < 70; i++) {
        if (D_800BA5E0[i] == arg0) {
            D_800BA5E0[i] = 0;
        }
    }
}
