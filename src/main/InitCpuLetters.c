// InitCpuLetters.c -- the orders in which the machine calls letters

#include "wof.h"

u8 consonantOrder[24] = "RSTLNCBDMHFYKJGPQVWXZ";
u8 vowelOrder[6] = "EAIOU";

/*
=====================
InitCpuLetters

The orders in which the machine calls letters.
=====================
*/
void InitCpuLetters(void) {
    StrCopy(cpuConsonants, consonantOrder);
    StrCopy(cpuVowels, vowelOrder);
}
