typedef unsigned char u8;
typedef signed int s32;

s32 func_800099B0(s32 arg0, s32 arg1) {
    s32 i;

    i = 0;
    while (((u8 *)arg0)[i] != 0 && ((u8 *)arg0)[i] != arg1) {
        i++;
    }
    if (((u8 *)arg0)[i] == 0) {
        return 0;
    }
    return arg0 + i;
}
