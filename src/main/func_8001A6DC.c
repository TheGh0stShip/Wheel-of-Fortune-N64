typedef unsigned char u8;
typedef signed int s32;
s32 func_800076E0(register s32 arg0);
s32 func_80009A74(s32 arg0);

s32 func_8001A6DC(s32 arg0) {
    s32 i;
    s32 len;
    u8 result;

    result = 32;
    len = func_80009A74(arg0);
    for (i = 0; i < len; i++) {
        if (func_800076E0(((u8 *)arg0)[i]) == 0) {
            result = ((u8 *)arg0)[i];
            break;
        }
    }
    return result;
}
