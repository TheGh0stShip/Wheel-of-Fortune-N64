// ResetMotors.c -- resetMotor on each controller that has a rumble pak

#include "wof.h"

/*
=====================
ResetMotors

ResetMotor on each controller that has a rumble pak.
=====================
*/
void ResetMotors(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if ((contPattern >> i) % 2 != 0) {
            if (rumbles[i].present != 0) {
                ResetMotor(i);
            }
        }
    }
}
