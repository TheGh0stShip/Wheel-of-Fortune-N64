typedef signed int s32;
typedef unsigned int u32;
s32 func_800A19D8(u32 arg0) {
    if (arg0 == 0) {
        return 0;
    }
    if (arg0 & 1) {
        return func_800A19D8(arg0 >> 1) + 1;
    }
    return func_800A19D8(arg0 >> 1);
}
