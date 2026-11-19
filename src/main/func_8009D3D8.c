typedef signed short s16;
typedef signed int s32;
extern s16 D_800FD2C8[][64];
void func_8009D67C(s32 arg0);
s32 func_800A4CF8(s32 arg0, s32 arg1, s32 arg2);

void func_8009D3D8(void) {
    s32 i;

    for (i = 0; i < 64; i++) {
        func_800A4CF8((s32)D_800FD2C8[i], 0, 128);
        D_800FD2C8[i][i] = 256;
        func_8009D67C((s32)D_800FD2C8[i]);
    }
}
