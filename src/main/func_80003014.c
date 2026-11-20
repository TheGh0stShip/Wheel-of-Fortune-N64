#include "wof.h"

extern s32 D_8004B718;
extern s16 *D_800A509C;
void func_80039718(s32, s16);
void func_80039778(s32, u8);
void func_800397D8(s32, u8);
void func_80049FA8(s32, s16);

void func_80003014(s32 arg0, register s32 arg1, register s32 arg2, register s32 arg3) {
    u8 sp10;
    u8 sp11;
    s16 sp12;

    sp10 = arg1;
    sp11 = arg2;
    sp12 = arg3;
    func_80049FA8(D_8004B718, D_800A509C[arg0]);
    func_800397D8(D_8004B718, sp10);
    func_80039778(D_8004B718, sp11);
    func_80039718(D_8004B718, sp12);
}
