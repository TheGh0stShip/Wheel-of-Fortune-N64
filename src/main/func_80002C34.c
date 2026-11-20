#include "wof.h"

s32 func_80002C34(s32 arg0) {
    func_80049FA8(D_8004B718, D_800A509C[arg0]);
    if ((D_800B81F0[arg0] = func_8003CE38(D_8004B718)) == 0) {
        return 1;
    }
    return 0;
}
