#include "wof.h"

void InitObjs(void) {
    s32 i;

    for (i = 0; i < 100; i++) {
        objst[i].unk_0C = 0;
        objst[i].index = i;
        objst[i].unk_04 = 0;
    }
    numObjs = 0;
    objst[0].unk_0C = 0;
    objst[0].next = 0;
}
