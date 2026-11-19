typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef double f64;
extern f64 D_800880C0;
extern f64 D_800FD098[][8];
f64 func_800A4F24(f64 arg0);

void func_8009C754(s32 arg0) {
    s32 i;
    s32 j;
    s32 k;
    s32 value;
    f64 sum;
    f64 tmp[64];

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            sum = 0.0;
            for (k = 0; k < 8; k++) {
                sum = sum + D_800FD098[k][j] * (f64)((s16 *)arg0)[i * 8 + k];
            }
            tmp[i * 8 + j] = sum;
        }
    }
    j = 0;
    while (j < 8) {
        for (i = 0; i < 8; i++) {
            sum = 0.0;
            for (k = 0; k < 8; k++) {
                sum = sum + D_800FD098[k][i] * tmp[k * 8 + j];
            }
            value = (s32)func_800A4F24(sum + D_800880C0);
            ((s16 *)arg0)[i * 8 + j] = (value < -256) ? -256 : ((value >= 256) ? 255 : (u16)value);
        }
        j++;
    }
}
