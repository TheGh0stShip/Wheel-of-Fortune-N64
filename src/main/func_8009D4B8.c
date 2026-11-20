#include "wof.h"

void func_8009D4B8(s32 arg0, s32 arg1) {
    register s32 *p;
    register s32 value;
    s16 sp10;
    s32 sp14;

    if (arg1 == 0) {
        p = (s32 *)arg0;
        value = *(s16 *)arg0;
        sp14 = 8;
        if (value < 0) {
            sp10 = value * -1;
            sp10 = (sp14 >> 1) + (u16)sp10;
            sp10 = sp10 / sp14;
            sp10 = -(u16)sp10;
        } else {
            sp10 = (value + (sp14 >> 1)) / sp14;
        }
        value = sp10;
        value = value & 0xFFFF;
        value = value | (sp10 << 16);
        p[0] = value;
        p[1] = value;
        p[2] = value;
        p[3] = value;
        p[4] = value;
        p[5] = value;
        p[6] = value;
        p[7] = value;
        p[8] = value;
        p[9] = value;
        p[10] = value;
        p[11] = value;
        p[12] = value;
        p[13] = value;
        p[14] = value;
        p[15] = value;
        p[16] = value;
        p[17] = value;
        p[18] = value;
        p[19] = value;
        p[20] = value;
        p[21] = value;
        p[22] = value;
        p[23] = value;
        p[24] = value;
        p[25] = value;
        p[26] = value;
        p[27] = value;
        p[28] = value;
        p[29] = value;
        p[30] = value;
        p[31] = value;
        return;
    }
    func_8009D67C(arg0);
    return;
}
