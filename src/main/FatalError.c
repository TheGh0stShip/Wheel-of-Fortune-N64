// FatalError.c -- report an error that the game cannot recover from, and stop

#include "wof.h"

/*
=====================
FatalError

Prints "ERROR: " and the message, then loops forever.
=====================
*/
void FatalError(char *msg) {
    PrintStr("ERROR: ");
    PrintStr(msg);
    PrintStr("\n");
    for (;;) {
    }
}
