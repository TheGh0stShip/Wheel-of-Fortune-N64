typedef unsigned char u8;
typedef signed int s32;
extern u8 D_800B9559[][21];

s32 func_800111F0(s32 arg0, s32 arg1, s32 arg2) {
    s32 limit;

    if (arg0 == 0 || arg0 == 3) {
        limit = 12;
    } else {
        limit = 14;
    }
    arg1 += arg2;
    do {
        if (D_800B9559[arg0][arg1] == 43) {
            return arg1;
        }
        arg1 += arg2;
    } while (arg1 >= 0 && arg1 < limit);
    return -1;
}
