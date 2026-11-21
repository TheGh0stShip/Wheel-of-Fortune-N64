// DecodeMovie.c -- decodes a number of frames of a movie into memory at once

#include "wof.h"

/*
=====================
DecodeMovie

Decodes a number of frames of a movie into memory at once.
=====================
*/
void DecodeMovie(s32 movie, s32 count, s16 *pictures, s32 *arg3) {
    s32 i;
    s32 unused;  /* NOTE: unused in the original */
    char *sp18;

    if (D_80086D58 != 0) {
        PopMemStack(1);
        func_800A4E58(0);
    }
    movieToMemory = 1;
    moviePictures = pictures;
    D_800B81E4 = arg3;
    curMovie = movie;
    movieMemMark = PushMemStack();
    movieDone = 0;
    sp18 = LoadMovie(movie);
    func_8009CEC0(sp18, movies[movie].unk_0C);
    for (i = 1; i < count; i++) {
        func_8009D244();
    }
    func_800A4E58(0);
    PopMemStack(1);
    movieToMemory = 0;
}
