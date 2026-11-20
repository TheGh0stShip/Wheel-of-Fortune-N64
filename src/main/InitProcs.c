#include "wof.h"

void InitProcs(void) {
    s32 i;

    for (i = 0; i < 70; i++) {
        procst[i].unk_00 = 0;
        procst[i].unk_04 = i;
    }
    numProcs = 0;
    procst[0].unk_00 = 0;
    procst[0].next = 0;
    D_800B61A4 = 0;
    for (i = 0; i < 70; i++) {
        blockOwners[i] = 0;
    }
}
