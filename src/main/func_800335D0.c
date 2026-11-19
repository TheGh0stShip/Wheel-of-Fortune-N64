typedef signed int s32;
typedef unsigned long long u64;
extern s32 func_80028B1C;
extern u64 D_80084218;
extern s32 D_800B40C4;
extern s32 D_800BA2C0;
extern s32 D_800BCD54;
extern s32 D_800BED98;
s32 func_800028E4();
s32 func_80005258();
s32 func_80015848();
u64 func_80044988();

void func_800335D0(void) {
    if (D_800B40C4 == 0) {
        return;
    }
    func_80005258();
    D_800BA2C0 = (s32)(func_80044988() / D_80084218);
    D_800BED98 = D_800BCD54;
    D_800BCD54 = 6;
    func_80015848(0, 0, ((s32)&func_80028B1C), 0x5020000);
    func_800028E4();
}
