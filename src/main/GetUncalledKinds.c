#include "wof.h"


s32 GetUncalledKinds(void) {
    s32 consonants;
    s32 vowels;
    u8 *p;

    vowels = 0;
    consonants = 0;
    for (p = uncalled; *p != 0; p++) {
        switch (*p) {
        case 'A':
        case 'E':
        case 'I':
        case 'O':
        case 'U':
            vowels++;
            break;
        case ' ':
            break;
        default:
            consonants++;
        }
    }
    if (consonants > 0 && vowels > 0) {
        return 4;
    }
    if (consonants == 0 && vowels > 0) {
        return 2;
    }
    if (consonants > 0 && vowels == 0) {
        return 3;
    }
    return 0;
}
