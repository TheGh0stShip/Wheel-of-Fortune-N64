// ClearBonusLetters.c -- takes the four letters chosen in the bonus round off the screen

#include "wof.h"

/*
=====================
ClearBonusLetters

Takes the four letters chosen in the bonus round off the screen.
=====================
*/
void ClearBonusLetters(void) {
    bonusLetterSlots[6].texture = 0;
    bonusLetterSlots[7].texture = 0;
    bonusLetterSlots[8].texture = 0;
    bonusLetterSlots[9].texture = 0;
}
