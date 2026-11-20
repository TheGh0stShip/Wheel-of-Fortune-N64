#include "wof.h"

void PrintNum(s32 num) {
    u8 buf[20];
    s32 i;
    s32 divisor;
    s32 digit;
    s32 value;

    value = num;
    if (value < 0) {
        value = value * -1;
    }
    buf[19] = 0;
    i = 18;
    for (divisor = 10; divisor <= 999999999; divisor = divisor * 10) {
        digit = value % divisor;
        value = value - digit;
        digit = digit / (divisor / 10);
        buf[i--] = digit + '0';
        if (value == 0) {
            break;
        }
    }
    if (num < 0) {
        buf[i--] = '-';
    }
    PrintStr(&buf[i + 1]);
}
