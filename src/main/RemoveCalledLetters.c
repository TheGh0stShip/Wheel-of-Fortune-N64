#include "wof.h"


void RemoveCalledLetters(u8 *letters) {
    u8 *found;
    u8 *p;

    p = letters;
    while (StrLen(p) > 0) {
        found = StrChr(uncalled, *p);
        if (found == 0) {
            StrCopy(p, p + 1);
        } else {
            p++;
        }
    }
}
