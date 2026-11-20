#include "wof.h"

s32 func_8000A56C(s32 arg0, s32 arg1);
void func_800219B8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 D_8006DDC4;
extern s32 *D_800B81E4;
extern s32 func_800345E8;

void func_80034950(void) {
    D_800B81E4 = &D_8006DDC4;
    func_800219B8(0x16, 0, 0x28, 0xF);
    func_8000A56C((s32)&func_800345E8, 0x05030000);
}
