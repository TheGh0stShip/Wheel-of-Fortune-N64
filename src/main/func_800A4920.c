#include "wof.h"
#include "mpeg/proto.h"


s32 func_800A4920(u8 arg0, s32 arg1, s32 arg2) {
    if ((arg0 != 0) && (arg0 != 1)) {
        (*(f64 *)arg2) = 0.0;
        return 1;
    }
    (*(f64 *)arg2) = ((((f64)arg0) * 65536.0) * 65536.0) + ((f64)((u32)arg1));
    (*(f64 *)arg2) = (*(f64 *)arg2) / 90000.0;
    return 0;
}
