typedef signed char s8;
typedef unsigned char u8;
typedef signed int s32;
extern u8 D_800B9559[][21];
extern s8 D_800B95AD[][21];

void func_800087F8(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 14; j++) {
            D_800B95AD[i][j] = D_800B9559[i][j];
        }
    }
}
