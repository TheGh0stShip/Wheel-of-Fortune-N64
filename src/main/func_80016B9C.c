typedef signed int s32;
s32 func_8000B5DC(s32 arg0, s32 arg1);
void func_80016944(s32 arg0, s32 arg1);

void func_80016B9C(s32 arg0) {
    s32 sp10;

    sp10 = func_8000B5DC(0x03000000, 0xFF000000);
    func_80016944(sp10, arg0);
}
