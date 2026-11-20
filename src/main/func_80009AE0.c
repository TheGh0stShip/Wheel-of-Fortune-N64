#include "wof.h"


void func_80009AE0(u8 *arg0, s32 arg1) {
    s32 i;
    u8 buf[24];

    if (arg1 == 0) {
        func_80009900(arg0, "0");
        return;
    }
    i = 19;
    buf[i--] = 0;
    while (i >= 0) {
        buf[i] = func_80009D2C(arg1 % 10) + '0';
        i--;
        arg1 = arg1 / 10;
    }
    i = 0;
    while (buf[i] == '0' && i < 20) {
        i++;
    }
    *arg0 = 0;
    if (arg1 < 0) {
        func_80009900(arg0, "-");
    }
    func_80009900(arg0, &buf[i]);
}
