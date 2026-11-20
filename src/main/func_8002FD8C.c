#include "wof.h"


void func_8002FD8C(void) {
    proc_t *task;

    if (D_800BCA00 == 0 || D_800BCD54 == 4) {
        return;
    }
    task = func_8000A990(0x7030000, -1);
    if (task == 0) {
        func_80009F38("ResetSolveTimer: Solve Timer Proc does not exist.\n");
    }
    func_8000AAB0(task, 8, 0);
}
