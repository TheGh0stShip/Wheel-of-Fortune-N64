// GetWedgeValue.c -- the value of curWedge; the 10000 wedge is 10000 only in its middle third, else
// BANKRUPT

#include "wof.h"

/*
=====================
GetWedgeValue

The value of curWedge; the 10000 wedge is 10000 only in its middle third, else BANKRUPT.
=====================
*/
s32 GetWedgeValue(void) {
    s32 result;
    s32 rem;

    if (wedges[curWedge].value == -10000) {
        rem = wedgeThird % 3;
        if (rem == 1) {
            result = 10000;
        } else {
            result = -1;
        }
    } else {
        result = wedges[curWedge].value;
    }
    return result;
}
