typedef signed int s32;
s32 func_8000A56C(s32 arg0, s32 arg1);
void func_800258BC(void);
s32 func_80027218(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_800223A4(s32 arg0, s32 arg1);
void func_80024370(void);

void func_80026DEC(void) {
    s32 pad;
    s32 task;

    task = func_8000A56C((s32)func_80024370, 0x05000000);
    func_80027218(task, 0, (s32)func_800223A4, 0x05000000);
    func_800258BC();
}
