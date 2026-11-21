// LoadMovie.c -- reads a movie from the cartridge into the memory stack

#include "wof.h"

/*
=====================
LoadMovie

Reads a movie from the cartridge into the memory stack.
=====================
*/
char *LoadMovie(s32 movie) {
    char *buf;

    buf = func_8000B924(*movies[movie].size + 1);
    ReadRom(movies[movie].rom, buf, *movies[movie].size + 1);
    return buf;
}
