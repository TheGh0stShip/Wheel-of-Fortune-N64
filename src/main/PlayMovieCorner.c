// PlayMovieCorner.c -- playMovie at (25, 20), the top left

#include "wof.h"

/*
=====================
PlayMovieCorner

PlayMovie at (25, 20), the top left.
=====================
*/
void PlayMovieCorner(s32 movie, s32 event) {
    PlayMovie(movie, event, 0x19, 0x14);
}
