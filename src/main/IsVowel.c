#include "wof.h"

/*
=====================
IsVowel

1 if a letter is in vowels.
=====================
*/
s32 IsVowel(register s32 letter) {
    u8 value;

    value = letter;
    if (StrChr(vowelLetters, value) != 0) {
        return 1;
    }
    return 0;
}
