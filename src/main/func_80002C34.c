typedef signed short s16;
typedef signed int s32;
extern s32 D_8004B718;
extern s16 *D_800A509C;
extern s32 D_800B81F0[];
s32 func_8003CE38(s32);
void func_80049FA8(s32, s16);

s32 func_80002C34(s32 arg0) {
    func_80049FA8(D_8004B718, D_800A509C[arg0]);
    if ((D_800B81F0[arg0] = func_8003CE38(D_8004B718)) == 0) {
        return 1;
    }
    return 0;
}
