#include "wof.h"

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
