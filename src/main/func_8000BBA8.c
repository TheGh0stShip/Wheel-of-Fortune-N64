typedef signed char s8;
typedef signed int s32;
typedef unsigned int u32;

extern s32 D_800B96AC;
extern s32 D_800BCD54;
extern s32 D_800BEDE4;
void func_80006B28(void);
void func_80016310(void);
void func_800174DC(void);
void func_8001A484(void);
void func_8002EC60(void);
void func_8002FE2C(void);
void func_80032BF0(void);
void func_800339E8(void);
void func_80033CBC(void);

void func_8000BBA8(void) {
    s8 pad0;

    do {
    } while (D_800BEDE4 != 0 && (u32)D_800B96AC < 100);
    D_800BCD54 = 2;
    func_800339E8();
    func_800174DC();
    func_8002FE2C();
    func_80006B28();
    func_80016310();
    func_80032BF0();
    func_8001A484();
    func_8002EC60();
    func_80033CBC();
}
