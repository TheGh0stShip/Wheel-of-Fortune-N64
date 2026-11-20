#include "wof.h"


void IntToStr(u8 *dst, s32 value) {
    s32 i;
    u8 buf[24];

    if (value == 0) {
        StrCopy(dst, "0");
        return;
    }
    i = 19;
    buf[i--] = 0;
    while (i >= 0) {
        buf[i] = Abs(value % 10) + '0';
        i--;
        value = value / 10;
    }
    i = 0;
    while (buf[i] == '0' && i < 20) {
        i++;
    }
    *dst = 0;
    if (value < 0) {
        StrCopy(dst, "-");
    }
    StrCopy(dst, &buf[i]);
}
