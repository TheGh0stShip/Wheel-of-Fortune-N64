#include "wof.h"

extern s8 D_800B9559[][21];
extern u8 D_800B9601[][21];
s32 func_800099B0(s32 arg0, s32 arg1);

void func_80007DAC(register s32 arg0) {
    u8 ch;
    s32 i;
    u8 *p;

    ch = arg0;
    for (i = 0; i < 4; i++) {
        p = D_800B9601[i];
        while (p != 0) {
            p = (u8 *)func_800099B0((s32)p, ch);
            if (p != 0) {
                D_800B9559[i][(p - D_800B9601[0]) - i * 21] = ch;
                p++;
            }
        }
    }
}
