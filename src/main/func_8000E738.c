typedef signed int s32;
void func_800289F4(s32 arg0, s32 arg1);
extern s32 D_800BCD54;
void func_80005700(void);
s32 func_80015848(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_8000E738(void) {
    s32 pad0;
    s32 result;

    D_800BCD54 = 1;
    func_80005700();
    result = func_80015848(0, 0, (s32)func_800289F4, 0x5030000);
}
