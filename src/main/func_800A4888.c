#include "wof.h"
#include "mpeg/proto.h"

void func_800A4888(u8 *arg0, s32 *arg1) {
    *arg1 = (arg0[0] & 0x7F & 0xFF) << 0xF;
    *arg1 = *arg1 | (arg0[1] << 7);
    *arg1 = *arg1 | (((u32)(arg0[2] & 0xFE & 0xFF) >> 1) & 0xFF);
}
