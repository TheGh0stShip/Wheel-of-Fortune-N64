// StopMovie.c -- ends the movie in play and frees its memory

#include "wof.h"

/*
=====================
StopMovie

Ends the movie in play and frees its memory.
=====================
*/
void StopMovie(void) {
    if (D_80086D58 != 0) {
        PopMemStack(1);
        func_800A4E58(0);
    }
    PopMemStack(1);
}
