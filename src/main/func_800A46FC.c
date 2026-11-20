#include "wof.h"
#include "mpeg/proto.h"

void func_800A46FC(void *arg0, s8 *arg1, s32 *arg2) {
    *arg1 = (((u8 *)arg0)[0] >> 3) & 1;
    *arg2 = ((((u8 *)arg0)[0] >> 1) & 3 & 0xFF) << 0x1E;
    *arg2 = *arg2 | (((u8 *)arg0)[1] << 0x16);
    *arg2 = *arg2 | (((((u8 *)arg0)[2] >> 1) & 0xFF) << 0xF);
    *arg2 = *arg2 | (((u8 *)arg0)[3] << 7);
    *arg2 = *arg2 | ((((u8 *)arg0)[4] >> 1) & 0xFF);
}
