typedef signed int s32;
typedef unsigned int u32;
s32 func_800A1B60(u32 arg0) {
    if (arg0 == 0) {
        return 0x20;
    }
    if (arg0 & 1) {
        return 0;
    }
    return func_800A1B60(arg0 >> 1) + 1;
}
