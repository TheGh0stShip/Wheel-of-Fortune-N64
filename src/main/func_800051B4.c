#include "wof.h"
#include "func_800051B4.h"


void func_800051B4(s32 arg0, s32 arg1, f32 arg2) {
    if (D_800BEE60[arg0].unk_00 == 0) {
        return;
    }
    D_800BEE60[arg0].unk_0C = arg1;
    D_800BEE60[arg0].unk_08 = arg2;
    D_800BEE60[arg0].unk_04 = 0;
}
