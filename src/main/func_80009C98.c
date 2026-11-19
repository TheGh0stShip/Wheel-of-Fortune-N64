typedef signed int s32;
s32 guRandom();                                     /* extern */

s32 func_80009C98(s32 arg0) {
    return guRandom() % arg0;
}
