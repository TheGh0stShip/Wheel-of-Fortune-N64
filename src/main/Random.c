// Random.c -- guRandom() modulo its argument

#include "wof.h"

/*
=====================
Random

GuRandom() modulo its argument.
=====================
*/
s32 Random(s32 range) {
    return guRandom() % range;
}
