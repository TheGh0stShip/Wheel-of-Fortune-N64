typedef signed short s16;
typedef signed int s32;

extern s32 D_8004B718;
extern s16 *D_800A509C;
s32 func_800396B8(s32, s32);
s32 func_80049FA8(s32, s32);

void func_800030E8(s32 arg0, s32 arg1) {
    func_80049FA8(D_8004B718, D_800A509C[arg0]);
    func_800396B8(D_8004B718, arg1);
}
