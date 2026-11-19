typedef signed int s32;
void func_80006BFC(void);
void func_8000963C(s32 arg0);
void func_8000A850(s32 arg0);
s32 func_8000A990(s32 arg0, s32 arg1);
void func_8000AAB0(s32 arg0, s32 arg1, s32 arg2);
void func_800132EC(s32 arg0);
void func_80015D4C(void);
void func_8001A5D0(void);
extern s32 D_800FB808;

void func_800177A4(void) {
    s32 handle;

    func_8000963C(1);
    func_80006BFC();
    func_800132EC(D_800FB808);
    handle = func_8000A990(D_800FB808 | 0x02000000, 0xFF0000FF);
    func_8000AAB0(handle, 0xF, 0);
    func_8000A850(0xF);
    func_80015D4C();
    func_8001A5D0();
}
