#include "wof.h"

/*
=====================
InitProcs

Clears procst and the data block owners.
=====================
*/
void InitProcs(void) {
    s32 i;

    for (i = 0; i < 70; i++) {
        procst[i].handler = 0;
        procst[i].id = i;
    }
    numProcs = 0;
    procst[0].handler = 0;
    procst[0].next = 0;
    D_800B61A4 = 0;
    for (i = 0; i < 70; i++) {
        blockOwners[i] = 0;
    }
}
