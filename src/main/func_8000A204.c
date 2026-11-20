#include "wof.h"

s32 func_8000A204(void) {
    s32 i;

    if (D_800BEE50 == 69) {
        func_80009F38("AllocProc: Out of Procs\n");
        return 0;
    }
    i = 1;
    while (i < 70) {
        if (D_800B82A0[i].unk_00 == 0) {
            D_800BEE50++;
            return (s32)&D_800B82A0[i];
        }
        i++;
    }
    func_80009F38("AllocProc: Reached end of procst.\n");
    return 0;
}
