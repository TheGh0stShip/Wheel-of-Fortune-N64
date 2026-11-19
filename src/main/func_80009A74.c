typedef unsigned char u8;
typedef signed int s32;

s32 func_80009A74(s32 arg0) {
    s32 len;

    len = 0;
    while (((u8 *)arg0)[len] != 0) {
        len++;
    }
    return len;
}
