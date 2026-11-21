// wof_abs.c -- an empty function and the absolute value
//
// SeedRandom ends off an 8-byte boundary with Abs right after, which happens only inside an object.
// Whether Random before it and PrintNum after it are this object's the text does not say.

#include "wof.h"

/*
=====================
SeedRandom

Empty, and nothing calls it. guess: the seed function that goes with Random, which draws from
guRandom's own sequence and has nothing to seed.
=====================
*/
void SeedRandom(s32 seed) {
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
