#ifndef N64DK_M2C_PRELUDE
#define N64DK_M2C_PRELUDE
typedef signed char s8; typedef unsigned char u8; typedef signed short s16; typedef unsigned short u16;
typedef signed int s32; typedef unsigned int u32; typedef signed long long s64; typedef unsigned long long u64;
typedef float f32; typedef double f64;
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
/* unhandled instructions become calls to an unprototyped function: any argument list compiles */
extern s32 m2c_unhandled();
#define M2C_ERROR m2c_unhandled
#define M2C_TRAP_IF m2c_unhandled
#define M2C_BREAK m2c_unhandled
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)
#define MULT_HI(a, b) ((s32)(((s64)(a) * (s64)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(a) * (u64)(b)) >> 32))
#define M2C_CARRY 0
#ifndef NULL
#define NULL ((void *)0)
#endif
#endif

extern s32 D_80000300;
extern s32 D_800AFE38;
extern s32 D_800AFE50;
extern s32 D_800B3988;
extern s32 D_800B3CB8;
extern s32 D_800B40C4;
extern s32 D_800B8294;
extern s32 D_800B9688;
extern s32 D_800B96AC;
extern s32 D_800B96B4;
extern u8 D_800B96C4;
extern s32 D_800B96C8;
extern s32 D_800B9CD0;
extern s32 D_800BC6F8;
extern s32 D_800BC6FC;
extern s32 D_800BCA40;
extern s32 D_800BCD50;
extern s32 D_800BCD58;
extern s32 D_800BEE00;
extern s32 D_800BEEA0;
extern u64 D_800FB810;
s32 func_80002348();
s32 func_8000420C();
s32 func_80005624();
s32 func_80009FD8();
s32 func_8000AF00();
s32 func_8000B780();
s32 func_8000E6B4();
s32 func_8000E738();
s32 func_80026FD4();
s32 func_8003CE58();
u64 func_80044988();
s32 func_80045498();
s32 func_800491A8();
s32 func_80049238();
s32 func_80049288();

void func_800068F0(void) {
    s32 sp18;

    func_80045498(((s32)&D_800AFE38), ((s32)&D_800AFE50), 1);
    func_80045498(((s32)&D_800B9688), ((s32)&D_800BCA40), 8);
    func_80045498(((s32)&D_800B9CD0), ((s32)&D_800BEE00), 8);
    if (D_80000300 == 2) {
        func_80049288(((s32)&D_800B96C8), ((s32)&D_800BC6F8), 13, 30, 1);
    } else {
        func_80049288(((s32)&D_800B96C8), ((s32)&D_800BC6F8), 13, 2, 1);
    }
    func_80049238(((s32)&D_800B96C8), ((s32)&D_800BCD58), ((s32)&D_800B9688));
    func_80049238(((s32)&D_800B96C8), ((s32)&D_800B3988), ((s32)&D_800B9CD0));
    D_800BEEA0 = func_800491A8(((s32)&D_800B96C8));
    sp18 = ((s32)func_80044988()) & 4095;
    for (;;) {
        if ((sp18--) <= 0) {
            break;
        }
        func_8003CE58();
    }
    D_800FB810 = 0;
    D_800B3CB8 = 0;
    D_800B8294 = 0;
    D_800B96AC = 0;
    D_800B96B4 = 0;
    D_800BCD50 = 0;
    func_8000B780();
    func_8000420C();
    func_80002348();
    func_80005624();
    D_800BC6FC = 37;
    D_800B40C4 = 1;
    func_80009FD8();
    func_8000AF00();
    if (D_800B96C4 != 0) {
        func_8000E6B4();
    } else {
        func_8000E738();
    }
    func_80026FD4();
}
