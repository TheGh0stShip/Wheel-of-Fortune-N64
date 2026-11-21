// FreeProcObjs.c -- frees the objs a proc owns

#include "wof.h"

/*
=====================
FreeProcObjs

Frees the objs a proc owns.
=====================
*/
void FreeProcObjs(s32 owner) {
    s32 i;
    s32 result;

    for (i = 0; i < 100; i++) {
        if (objst[i].owner == owner) {
            result = FreeObj(&objst[i]);
            if (result == 1) {
                // NOTE: empty in retail: what the original did with a freed obj compiled to nothing
            }
        }
    }
}
