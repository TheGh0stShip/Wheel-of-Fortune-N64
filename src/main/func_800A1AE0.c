#include "wof.h"
#include "mpeg/proto.h"

s32 func_800A1AE0(s32 arg0) {
    if (arg0 == 0) {
        return 32;
    }
    if (arg0 < 0) {
        return 0;
    }
    return func_800A1AE0(arg0 << 1) + 1;
}
