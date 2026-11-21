// ClearCategory.c -- takes the letters of the category off the screen

#include "wof.h"


/*
=====================
ClearCategory

Takes the letters of the category off the screen.
=====================
*/
void ClearCategory(void) {
    s32 i;

    for (i = 0; i < 22; i++) {
        categoryImages[i].texture = 0;
    }
}
