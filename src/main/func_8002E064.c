#include "wof.h"


s32 func_8002E064(void) {
    s32 result;

    result = func_8000A990(0x1020000, -1);
    if (result == 0) {
        func_80009F38("SolvePuzzleProc Proc: cursor proc does not exist\n");
    }
    return result;
}
