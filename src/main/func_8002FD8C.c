typedef signed int s32;
extern s32 D_80001928;
extern s32 D_800BCA00;
extern s32 D_800BCD54;
void func_80009F38(void *arg0);
s32 func_8000A990(s32 arg0, s32 arg1);
void func_8000AAB0(s32 arg0, s32 arg1, s32 arg2);

void func_8002FD8C(void) {
    s32 obj;

    if (D_800BCA00 == 0 || D_800BCD54 == 4) {
        return;
    }
    obj = func_8000A990(0x7030000, -1);
    if (obj == 0) {
        func_80009F38(&D_80001928);
    }
    func_8000AAB0(obj, 8, 0);
}
