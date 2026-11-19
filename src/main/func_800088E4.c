typedef signed char s8;
typedef unsigned char u8;
typedef signed int s32;

extern s8 D_800B9559[][21];
extern u8 D_800B95AD[][21];
extern u8 D_800B9601[][21];

s32 func_800088E4(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 14; j++) {
            if (D_800B9601[i][j] != D_800B95AD[i][j]) {
                return 0;
            }
        }
    }
    i = 0;
    while (i < 4) {
        for (j = 0; j < 14; j++) {
            D_800B9559[i][j] = D_800B9601[i][j];
        }
        i++;
    }
    return 1;
}
