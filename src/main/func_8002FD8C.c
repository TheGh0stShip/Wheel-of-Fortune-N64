#include "wof.h"


void func_8002FD8C(void) {
    s32 obj;

    if (D_800BCA00 == 0 || D_800BCD54 == 4) {
        return;
    }
    obj = func_8000A990(0x7030000, -1);
    if (obj == 0) {
        func_80009F38("ResetSolveTimer: Solve Timer Proc does not exist.\n");
    }
    func_8000AAB0(obj, 8, 0);
}
