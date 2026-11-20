#include "wof.h"

f64 func_80089490(void) {
    s32 sec;
    s32 frac;

    func_800A4F74((s32)&sec, 0);
    return (f64)sec + (f64)frac / D_80087E98;
}
