#include "wof.h"

/*
=====================
Abs

The absolute value.
=====================
*/
s32 Abs(s32 value) {
    if (value < 0) {
        value = value * -1;
    }
    return value;
}
