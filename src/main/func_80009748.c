typedef signed char s8;
typedef unsigned char u8;
typedef signed int s32;

s32 func_80009748(s32 arg0, s32 arg1, s32 arg2) {
    s32 i;
    s32 j;

    i = 0;
    j = 0;
    while (i < arg2) {
        ((s8 *)arg0)[i] = ((u8 *)arg1)[j];
        if (((u8 *)arg1)[j] != 0) {
            j++;
        }
        i++;
    }
    return arg0;
}
