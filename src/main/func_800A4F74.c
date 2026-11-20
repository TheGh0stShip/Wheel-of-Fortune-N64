#include "wof.h"
#include "mpeg/proto.h"

struct gd_4_s32 { u8 pad[0x4]; s32 v; };

s32 func_800A4F74(s32 arg0, ...) {
    s32 sp10;

    sp10 = (s32)osGetTime();
    (*(s32 *)arg0) = (s32)(sp10 / D_80084218);
    sp10 = (s32)(sp10 % D_80084218);
    ((struct gd_4_s32 *)arg0)->v = (s32)(((s64)sp10 * 0xF4240) / D_80084218);
    return 0;
}
