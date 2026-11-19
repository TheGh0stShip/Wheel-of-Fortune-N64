typedef signed char s8;
typedef unsigned char u8;
typedef signed int s32;

s32 func_80009900(s32 arg0, s32 arg1) {
    s32 i;

    i = 0;
    while (((u8 *)arg1)[i] != 0) {
        ((s8 *)arg0)[i] = ((u8 *)arg1)[i];
        i++;
    }
    ((s8 *)arg0)[i] = ((u8 *)arg1)[i];
    return arg0;
}
