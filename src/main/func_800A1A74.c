#include "wof.h"
#include "mpeg/proto.h"

u32 func_800A1A74(u32 arg0) {
    if (arg0 == 0) {
        return 0U;
    }
    if (arg0 & 1) {
        return arg0;
    }
    return arg0 >> 1;
}
