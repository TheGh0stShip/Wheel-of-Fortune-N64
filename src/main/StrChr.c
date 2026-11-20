#include "wof.h"

u8 *StrChr(u8 *str, s32 c) {
    s32 i;

    i = 0;
    while (str[i] != 0 && str[i] != c) {
        i++;
    }
    if (str[i] == 0) {
        return 0;
    }
    return str + i;
}
