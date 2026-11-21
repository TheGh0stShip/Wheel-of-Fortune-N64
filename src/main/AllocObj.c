// AllocObj.c -- a free entry of objst, or 0 when none is left

#include "wof.h"

/*
=====================
AllocObj

A free entry of objst, or 0 when none is left.
=====================
*/
obj_t *AllocObj(void) {
    s32 i;

    if (numObjs == 100) {
        FatalError("AllocObj: Out of Objects\n");
        return 0;
    }
    i = 1;
    while (i < 100) {
        if (objst[i].draw == 0) {
            numObjs++;
            return &objst[i];
        }
        i++;
    }
    FatalError("AllocObj: Reached end of objst.\n");
    return 0;
}
