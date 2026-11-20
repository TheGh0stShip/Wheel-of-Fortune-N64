#include "wof.h"

void func_800335D0(void) {
    if (D_800B40C4 == 0) {
        return;
    }
    func_80005258();
    D_800BA2C0 = (s32)(osGetTime() / D_80084218);
    D_800BED98 = D_800BCD54;
    D_800BCD54 = 6;
    func_80015848(0, 0, func_80028B1C, 0x5020000);
    func_800028E4();
}
