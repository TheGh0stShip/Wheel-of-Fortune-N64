#include "wof.h"

s32 func_8000A56C(s32, s32);
void func_800258BC(void);
s32 func_80027218(s32, s32, s32, s32);
void func_80022530(void);
void func_80024868(void);

void func_80026E50(void) {
    s32 pad;
    s32 sp14;

    sp14 = func_8000A56C((s32)func_80024868, 0x05000000);
    func_80027218(sp14, 0, (s32)func_80022530, 0x05000000);
    func_800258BC();
}
