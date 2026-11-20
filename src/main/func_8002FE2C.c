#include "wof.h"

s32 func_8000A56C(s32 arg0, s32 arg1);
extern s32 D_800B9CF0;
void func_8002F338(void);

void func_8002FE2C(void) {
    D_800B9CF0 = 0;
    func_8000A56C((s32)func_8002F338, 0x07010000);
}
