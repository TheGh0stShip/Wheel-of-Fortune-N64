#include "wof.h"

extern s32 D_80001850;
void func_80009F38(s32 *arg0);
s32 func_8000A990(s32 arg0, s32 arg1);

s32 func_8002E064(void) {
    s32 result;

    result = func_8000A990(0x1020000, -1);
    if (result == 0) {
        func_80009F38(&D_80001850);
    }
    return result;
}
