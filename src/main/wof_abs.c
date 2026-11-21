// wof_abs.c -- an empty function and the absolute value
//
// func_80009D08 ends off an 8-byte boundary with Abs right after, which happens only inside an object.
// Whether Random before it and PrintNum after it are this object's the text does not say.

#include "wof.h"

void func_80009D08(s32 arg0) {
}

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
