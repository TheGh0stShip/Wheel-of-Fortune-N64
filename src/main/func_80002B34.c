typedef signed short s16;
typedef signed int s32;

extern s32 D_8004B718;
extern s16 *D_800A509C;
extern s32 D_800B81F0[];
s32 func_8003CE38(s32);
void func_80049FA8(s32, s16);
void func_80049FC8(s32);

void func_80002B34(void) {
    s32 i;

    for (i = 31; i > 0; i--) {
        if (D_800A509C[i] != -1) {
            func_80049FA8(D_8004B718, D_800A509C[i]);
            if ((D_800B81F0[i] = func_8003CE38(D_8004B718)) == 0) {
                func_80049FC8(D_8004B718);
            }
        }
    }
}
