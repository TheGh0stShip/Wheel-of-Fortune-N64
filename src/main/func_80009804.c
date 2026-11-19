typedef signed char s8;
typedef unsigned char u8;
typedef signed int s32;

s32 func_80009804(s32 arg0, s32 arg1) {
    s32 i;
    s32 j;

    i = 0;
    while (((u8 *)arg0)[i] != 0) {
        i++;
    }
    j = 0;
    while (((u8 *)arg1)[j] != 0) {
        ((s8 *)arg0)[i] = ((u8 *)arg1)[j];
        i++;
        j++;
    }
    ((s8 *)arg0)[i] = ((u8 *)arg1)[j];
    return arg0;
}
