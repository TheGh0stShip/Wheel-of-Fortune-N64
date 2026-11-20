#include "wof.h"

extern s32 D_8004B718;
extern s16 *D_800A509C;

void func_80002F58(s32 arg0) {
    func_80049FA8(D_8004B718, D_800A509C[arg0]);
    func_8003CDE8(D_8004B718);
    func_80049F58(D_8004B718, D_800A509C[arg0]);
    D_800A509C[arg0] = -1;
}
